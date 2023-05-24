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
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };

	JsonOperator::GetJSONFloat(TITLE_JSON, "ChangeSceneButton", "posX", pos.x);
	JsonOperator::GetJSONFloat(TITLE_JSON, "ChangeSceneButton", "posY", pos.y);
	pStartButton = ButtonManager::CreateSceneChangeButton(this, pos, SCENE_ID_PLAY, "GameStartButton.png");

	JsonOperator::AppendToJSONFileString(TITLE_JSON, "sec", "key", "hello");
	JsonOperator::AppendToJSONFileFloat(TITLE_JSON, "OptionButton", "posX", 100);


}

//更新
void StartScene::Update()
{	
}

//描画
void StartScene::Draw()
{
}

//開放
void StartScene::Release()
{
}