#include "TutorialScene.h"
#include "TutorialStage.h"
#include "Player.h"
#include "Controller.h"
#include "Syari.h"

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{
}

//������
void TutorialScene::Initialize()
{
	
	//CharacterInstantiate<Player>(this, "syari.fbx");
	Instantiate<Syari>(this);
	Instantiate<Controller>(this);
	Instantiate<TutorialStage>(this);
}

//�X�V
void TutorialScene::Update()
{
}

//�`��
void TutorialScene::Draw()
{
}

//�J��
void TutorialScene::Release()
{
}