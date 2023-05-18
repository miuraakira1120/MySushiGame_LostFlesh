#include <Windows.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "global.h"
#include "RootObject.h"
#include "SceneManager.h"
#include "Model.h"
#include "Image.h"
#include "Camera.h"
#include "Input.h"
#include "Audio.h"
#include "Text.h"
#include "../Syari.h"
#include "../Time.h"
#include "../Controller.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
#include "../Pause.h"
#include "../Imgui_Obj.h"
#include "../Engine/JsonOperator.h"

#pragma comment(lib,"Winmm.lib")

//定数宣言
const char* WIN_CLASS_NAME = "鮮度命";	//ウィンドウクラス名
const int FPS = 60;


//プロトタイプ宣言
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


// エントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
//#if defined(DEBUG) | defined(_DEBUG)
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif

	srand((unsigned)time(NULL));
	SetCurrentDirectory("Assets");

	//初期化ファイル（setup.ini）から必要な情報を取得
	int screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");		//スクリーンの幅
	int screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");	//スクリーンの高さ
	int fpsLimit = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");				//FPS（画面更新速度）
	int isDrawFps = GetPrivateProfileInt("DEBUG", "ViewFps", 0, ".\\setup.ini");	

	//ウィンドウを作成
	HWND hWnd = InitApp(hInstance, screenWidth, screenHeight, nCmdShow);

	//Direct3D準備
	Direct3D::Initialize(hWnd, screenWidth, screenHeight);

	{
		//GUI初期化
#if _DEBUG
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontDefault();
		io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX11_Init(Direct3D::pDevice_, Direct3D::pContext_);
		ImGui::SetNextWindowSize(ImVec2(320, 100));
#endif
	}

	//カメラを準備
	Camera::Initialize();

	//入力処理（キーボード、マウス、コントローラー）の準備
	Input::Initialize(hWnd);

	//オーディオ（効果音）の準備
	Audio::Initialize();

	//JsonOperator初期化
	JsonOperator::Initialize();


	//ルートオブジェクト準備
	//すべてのゲームオブジェクトの親となるオブジェクト
	RootObject* pRootObject = new RootObject;
	pRootObject->Initialize();

	//シーンマネージャーのポインタを入れる
	SceneManager* pSceneManager;
	pSceneManager = (SceneManager*)pRootObject->FindObject("SceneManager");

	//Timeのイニシャライズ
	Time::Initialize(FPS);

	//Pauseのイニシャライズ
	Pause::Initialize(pSceneManager);

#if _DEBUG
	//imguiのイニシャライズ
	Imgui_Obj::Initialize(pSceneManager);
#endif

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり（こっちが優先）
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし（ここでゲームの処理）
		else
		{
			//時間計測
			timeBeginPeriod(1);	//時間計測の制度を上げる
			static int FPS = 0;								//画面更新回数のカウンタ
			static DWORD lastFpsResetTime = timeGetTime();	//最後にキャプションにFPSを表示した
			static DWORD lastUpdateTime = timeGetTime();	//最後に画面を更新した時間
			DWORD nowTime = timeGetTime();					//現在の時間

			//キャプションに現在のFPSを表示する
			if (isDrawFps)
			{
				//1秒（1000ミリ秒）経ったら
				if (nowTime - lastFpsResetTime > 1000)
				{
					//FPSの値を表示
					char string[16];
					wsprintf(string, "FPS:%d", FPS);
					SetWindowText(GetActiveWindow(), string);
					FPS = 0;
					lastFpsResetTime = nowTime;
				}
			}


			//指定した時間（FPSを60に設定した場合は60分の1秒）経過していたら更新処理
			if ((nowTime - lastUpdateTime) * fpsLimit > 1000.0f)
			{
#if _DEBUG
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
#endif

				//時間計測関連
				lastUpdateTime = nowTime;	//現在の時間（最後に画面を更新した時間）を覚えておく
				FPS++;						//画面更新回数をカウントする

				//入力（キーボード、マウス、コントローラー）情報を更新
				Input::Update();

				//Pauseを更新
				Pause::Update();

				//Pauseしていてなかったら
				if (!Pause::GetPause())
				{
					//全オブジェクトの更新処理
					//ルートオブジェクトのUpdateを呼んだあと、自動的に子、孫のUpdateが呼ばれる
					pRootObject->UpdateSub();
				}
#if _DEBUG
				//imguiのアップデート
				Imgui_Obj::Update();
#endif
				//カメラを更新
				Camera::Update();

				//Timeの更新
				Time::Update();

				//このフレームの描画開始
				Direct3D::BeginDraw();

				//全オブジェクトを描画
				//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
				//pRootObject->DrawSub();
				
				//左画面描画
				{
					Direct3D::SetViewPort(0);

					Syari* pSyari = (Syari*)pRootObject->FindObject("Syari");
					//controllerクラスのポインタを入れる
					Controller* pController = (Controller*)pRootObject->FindObject("Controller");

					if (pSyari != nullptr)
					{
						Camera::SetTarget(pSyari->GetPosition());
						Camera::SetPosition(pController->GetCameraPos());
					}
					


					//Camera::SetPosition(XMFLOAT3(0, 0, -10));
					Camera::Update();

					//全オブジェクトを描画
					//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
					pRootObject->DrawSub();
				}



				//右画面描画
				{
					Direct3D::SetViewPort(1);

					Syari* pSyari = (Syari*)pRootObject->FindObject("Syari");
					//controllerクラスのポインタを入れる
					Controller* pController;
					pController = (Controller*)pRootObject->FindObject("Controller");

					//if (pSyari != nullptr)
					//{
					//	Camera::SetTarget(pSyari->GetPosition());
					//	Camera::SetPosition(XMFLOAT3(0, 10, 0));


					//	/*Camera::SetPosition(XMFLOAT3(10, 0, 0));
					//	Camera::SetPosition(pController->GetPosition());*/
					//}

					//Camera::Update();

					//////全オブジェクトを描画
					//////ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
					//pRootObject->DrawSub();
				}

#if _DEBUG
				ImGui::Render();
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
				//ポーズ画面の描画
				Pause::Draw();

				//描画終了
				Direct3D::EndDraw();

				//ちょっと休ませる
				Sleep(1);
			}
			timeEndPeriod(1);	//時間計測の制度を戻す
		}
	}

	
	Audio::Release();
	Model::AllRelease();
	Image::AllRelease();
#if _DEBUG
	Imgui_Obj::Release();
#endif
	pRootObject->ReleaseSub();
	SAFE_DELETE(pRootObject);
	Direct3D::Release();
#if _DEBUG
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
#endif

	return 0;
}


//ウィンドウの作成
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);					//この構造体のサイズ
	wc.hInstance = hInstance;						//インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;				//ウィンドウクラス名
	wc.lpfnWndProc = WndProc;						//ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;				//スタイル（デフォルト）
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	//アイコン
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);	//小さいアイコン
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//マウスカーソル
	wc.lpszMenuName = nullptr;						//メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//背景（白）
	RegisterClassEx(&wc);

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, screenWidth, screenHeight };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

	//タイトルバーに表示する内容
	char caption[64];
	GetPrivateProfileString("SCREEN", "Caption", "***", caption, 64, ".\\setup.ini");

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,					//ウィンドウクラス名
		caption,						//タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW,			//スタイル（普通のウィンドウ）
		CW_USEDEFAULT,					//表示位置左（おまかせ）
		CW_USEDEFAULT,					//表示位置上（おまかせ）
		winRect.right - winRect.left,	//ウィンドウ幅
		winRect.bottom - winRect.top,	//ウィンドウ高さ
		nullptr,						//親ウインドウ（なし）
		nullptr,						//メニュー（なし）
		hInstance,						//インスタンス
		nullptr							//パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	switch (msg)
	{
	//ウィンドウを閉じた
	case WM_DESTROY:
		PostQuitMessage(0);	//プログラム終了
		return 0;

	//マウスが動いた
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}