#include "TutorialStage.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "ImageBase.h"

//コンストラクタ
TutorialStage::TutorialStage(GameObject* parent)
    :GameObject(parent, "TutorialStage")
{
}

//デストラクタ
TutorialStage::~TutorialStage()
{
}

//初期化
void TutorialStage::Initialize()
{
    hModel_ = Model::Load("Tutorial.fbx");
    assert(hModel_ >= 0);
}

//更新
void TutorialStage::Update()
{
    //プレイヤーを探してポジションをゲット（後で変更する）
    Syari* pSyari = (Syari*)FindObject("Syari");
    XMFLOAT3 playerPos =  pSyari->GetPosition();

    //ジャンプのチュートリアル画像表示（後で変更する）
    static bool flag = false;
    if (playerPos.z <= -16.0f && playerPos.z >= -34.0f && flag == false)
    {

        InstantiateImage<ImageBase>(this, "BlackBack.jpg", transform_.position_, transform_.rotate_, XMFLOAT3(0.6f, 0.6, 1.0f), 126);
        flag = true;
    }
}

//描画
void TutorialStage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void TutorialStage::Release()
{
}