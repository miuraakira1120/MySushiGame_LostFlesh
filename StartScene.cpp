#include "StartScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "ButtonManager.h"
#include "Engine/IniOperator.h"
#include "Imgui_Obj.h"
#include "Pause.h"
#include "Engine/JsonOperator.h"

//�R���X�g���N�^
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), hPict_(-1)
{
}

//������
void StartScene::Initialize()
{
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };

	JsonOperator::GetJSONFloat(TITLE_JSON, "ChangeSceneButton", "posX", pos.x);
	JsonOperator::GetJSONFloat(TITLE_JSON, "ChangeSceneButton", "posY", pos.y);
	pStartButton = ButtonManager::CreateSceneChangeButton(this, pos, SCENE_ID_PLAY, "GameStartButton.png");

}

//�X�V
void StartScene::Update()
{	
}

//�`��
void StartScene::Draw()
{
	/*Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
}

//�J��
void StartScene::Release()
{
}