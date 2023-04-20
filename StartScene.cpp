#include "StartScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "ButtonManager.h"

//コンストラクタ
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), hPict_(-1)
{
}

//初期化
void StartScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("start.jpg");
	assert(hPict_ >= 0);

	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	ButtonManager::CreateTestButton(this,pos);
}

//更新
void StartScene::Update()
{
	/*if (Input::IsMouseButtonDown(0) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}*/

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