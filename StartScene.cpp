#include "StartScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "ButtonManager.h"
#include "Engine/IniOperator.h"
#include "Imgui_Obj.h"
#include "Pause.h"
#include "Engine/JsonOperator.h"

//コンストラクタ
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), hPict_(-1)
{
}

//初期化
void StartScene::Initialize()
{
	////画像データのロード
	//hPict_ = Image::Load("start.jpg");
	//assert(hPict_ >= 0);

	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	pStartButton = ButtonManager::CreateSceneChangeButton(this, pos, SCENE_ID_PLAY, "GameStartButton.png");

	/*int iniListButton = IniOperator::AddList(iniFileName, "TitleButton");
	pStartButton->SetPosition(IniOperator::GetValue(iniListButton, "ChangeSceneButtonX",0), IniOperator::GetValue(iniListButton, "ChangeSceneButtonY",0), 0);*/

	//JsonOperator::AppendToJSONFileFloat(TITLE_JSON, "Button","value", 22.4);
	
	//JsonOperator::GetJSONFloat(TITLE_JSON, "Button", "ChangeSceneButtonX", pos.x);
	//JsonOperator::GetJSONFloat(TITLE_JSON, "Button", "ChangeSceneButtonY", pos.y);
	pStartButton->SetPosition(pos);


	/*string str = "yo";
	if (JsonOperator::GetJSONString("test.json", "key", str))
	{
		int i = 0;
	}
	int a = 0;*/

	/*float i = 0;
	if (JsonOperator::GetJSONFloat("test.json","Button", "posX", i))
	{
		int j = 0;
	}
	int ij= 0;
	if (JsonOperator::GetJSONFloat("test.json", "Button", "posY", i))
	{
		int j = 0;
	}*/

	

	
}

//更新
void StartScene::Update()
{
	//SetCurrentDirectory("Assrets");
	//int isPlaySe_ = GetPrivateProfileInt("Option", "Key", 1, ".\\/Config/test.ini");
	////filesystem
	//int a = 7;

#if _DEBUG
	/*pStartButton->SetPosition(IniOperator::GetValue(iniListButton, "ChangeSceneButtonX"), IniOperator::GetValue(iniListButton, "ChangeSceneButtonY"), 0);*/
	XMFLOAT3 pos = { 0,0,0 };
	//JsonOperator::GetJSONFloat(TITLE_JSON, "Button", "ChangeSceneButtonX", pos.x);
	//JsonOperator::GetJSONFloat(TITLE_JSON, "Button", "ChangeSceneButtonY", pos.y);
	pStartButton->SetPosition(pos);
#endif
	
}

//描画
void StartScene::Draw()
{
	/*Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
}

//開放
void StartScene::Release()
{
}