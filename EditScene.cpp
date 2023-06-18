#include "EditScene.h"
#include "Engine/JsonOperator.h"
#include "Imgui_Obj.h"


//�R���X�g���N�^
EditScene::EditScene(GameObject* parent)
	: GameObject(parent, "EditScene"), modeUI(UI_Type::NONE), prevModeUI(UI_Type::NONE)
{
}

//������
void EditScene::Initialize()
{
	
}

//�X�V
void EditScene::Update()
{
	
	modeUI = static_cast<UI_Type>(Imgui_Obj::GetUIType());

	//�O�̍쐬���Ă���UI�̃^�C�v�ƈ������
	if (modeUI != prevModeUI)
	{
		//�q�������ׂď���
		KillAllChildren();

		//�Ή�����UI���쐬
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

//�`��
void EditScene::Draw()
{
}

//�J��
void EditScene::Release()
{
}