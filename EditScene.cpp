#include "EditScene.h"
#include "Engine/JsonOperator.h"
#include "Imgui_Obj.h"


//コンストラクタ
EditScene::EditScene(GameObject* parent)
	: GameObject(parent, "EditScene"), modeUI(UI_Type::NONE), prevModeUI(UI_Type::NONE)
{
}

//初期化
void EditScene::Initialize()
{
	
}

//更新
void EditScene::Update()
{
	
	modeUI = static_cast<UI_Type>(Imgui_Obj::GetUIType());

	//前の作成していたUIのタイプと違ったら
	if (modeUI != prevModeUI)
	{
		//子供をすべて消す
		KillAllChildren();

		//対応したUIを作成
		switch (modeUI)
		{
		case UI_Type::NONE:
			break;
		case UI_Type::PAUSE:
			InstanceManager::AllCreateImage(JsonOperator::PAUSE_IMAGE_JSON, this);
			InstanceManager::AllCreateButton(JsonOperator::PAUSE_BUTTON_JSON, this);
			break;
			
		case UI_Type::TUTORIAL_JUMP:
			InstanceManager::AllCreateImage(JsonOperator::TUTORIAL_JUMP_IMAGE_JSON, this);
			break;

		case UI_Type::TYPE_MAX:
			break;
		default:
			break;
		}
	}
	prevModeUI = modeUI;
}

//描画
void EditScene::Draw()
{
}

//開放
void EditScene::Release()
{
}