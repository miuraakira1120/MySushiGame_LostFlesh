#include "StartScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "ButtonManager.h"

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

	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	ButtonManager::CreateTestButton(this,pos);
}

//�X�V
void StartScene::Update()
{
	SetCurrentDirectory("Assrets");
	int isPlaySe_ = GetPrivateProfileInt("Option", "Key", 1, ".\\/Config/test.ini");
	//filesystem
	int a = 7;
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