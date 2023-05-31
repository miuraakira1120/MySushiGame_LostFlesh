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

	JsonOperator::GetJSONFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posX", pos.x);
	JsonOperator::GetJSONFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posY", pos.y);
	pStartButton = ButtonManager::CreateSceneChangeButton(this, pos, SCENE_ID_PLAY, "GameStartButton.png");

	JsonOperator::AppendToJSONFileString(JsonOperator::TITLE_JSON, "sec", "key", "hello");
	JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "OptionButton", "posX", 100);

	XMFLOAT3 a = { 1,2,3 };
	XMFLOAT3 aa = { 4,5,6 };
	XMFLOAT3 aaa = { 7,8,9 };


	//InstanceManager::InstantiateInfoJSON testInfo = { "parent", "image", "name", a, aa, aaa };
	//JsonOperator::WhiteInstanceInfo(JsonOperator::TEST_JSON, "sec", testInfo);

	//InstanceManager::CreateInfoJSON getInfo;
	//JsonOperator::GetInstanceInfo(JsonOperator::TEST_JSON, "sec", getInfo);
	InstanceManager::AllCreateButton(JsonOperator::TITLE_BUTTON_JSON, instanceList, this);
	InstanceManager::AllCreateImage(JsonOperator::TITLE_IMAGE_JSON, instanceList, this);

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