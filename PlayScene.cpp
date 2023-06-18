#include "PlayScene.h"
#include "Syari.h"
#include "Maguro.h"
#include "Stage.h"
#include "Controller.h"
#include "RedBox.h"
#include "BlueBox.h"
#include "Goal.h"
#include "Engine/Camera.h"
#include "Cannon.h"
#include "SalmonRoe.h"
#include "Engine/Image.h"
#include "Player.h"
#include "ImageBase.h"


//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pos(0), hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	//CharacterInstantiate<Player>(this, "syari.fbx");
	Instantiate<Syari>(this);
	Instantiate<Controller>(this);
	Instantiate<Stage>(this);
	InstantiateImage<ImageBase>(this, "PC.jpg", XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
}

//更新
void PlayScene::Update()
{
	pos += UVSCROLL_SPEED;
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
