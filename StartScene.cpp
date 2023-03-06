#include "StartScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), hPict_(-1)
{
}

//������
void StartScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("start.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void StartScene::Update()
{
	if (Input::IsMouseButtonDown(0) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}

}

//�`��
void StartScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void StartScene::Release()
{
}