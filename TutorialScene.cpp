#include "TutorialScene.h"
#include "TutorialStage.h"
#include "Player.h"
#include "Controller.h"
#include "Syari.h"

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{
}

//初期化
void TutorialScene::Initialize()
{
	
	//CharacterInstantiate<Player>(this, "syari.fbx");
	Instantiate<Syari>(this);
	Instantiate<Controller>(this);
	Instantiate<TutorialStage>(this);
}

//更新
void TutorialScene::Update()
{
}

//描画
void TutorialScene::Draw()
{
}

//開放
void TutorialScene::Release()
{
}