#include "Cannon.h"
#include "Engine/Model.h"
#include "Syari.h"

//コンストラクタ
Cannon::Cannon(GameObject* parent)
    :GameObject(parent, "Cannon"), hModel_(-1)
{
}

//デストラクタ
Cannon::~Cannon()
{
}

//初期化
void Cannon::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Cannon.fbx");
    assert(hModel_ >= 0);

    Model::SetAnimFrame(hModel_, 1, 1200, 3.0f);
}

//更新
void Cannon::Update()
{
    Syari* pSyari = (Syari*)FindObject("Syari");
    transform_.position_ = pSyari->GetPosition();
}

//描画
void Cannon::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Cannon::Release()
{
}