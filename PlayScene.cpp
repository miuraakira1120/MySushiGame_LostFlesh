#include "PlayScene.h"
#include "Syari.h"
#include "Maguro.h"
#include "Stage.h"
#include "Controller.h"
#include "RedBox.h"
#include "BlueBox.h"

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
{
	Instantiate<Syari>(this);
	Instantiate<Stage>(this);
	Instantiate<Controller>(this);
	Instantiate<RedBox>(this);
	Instantiate<BlueBox>(this);
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
