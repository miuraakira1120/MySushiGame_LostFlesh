#include "Goal.h"
#include "Engine/Model.h"
#include "Stage.h"

//コンストラクタ
Goal::Goal(GameObject* parent)
    :GameObject(parent, "Goal"), hModel_(-1)
{
}

//デストラクタ
Goal::~Goal()
{
}

//初期化
void Goal::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Dishes.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = { 0, 0, 5 };
    transform_.scale_ = { 0.25f, 0.25f , 0.25f };
}

//更新
void Goal::Update()
{
    transform_.rotate_.y += 0.5f;

    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    RayCastData data;
    data.start = transform_.position_;   //レイの発射位置
    data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &data); //レイを発射

    //レイが当たったら
    if (data.hit)
    {
        //その分位置を下げる
        transform_.position_.y -= data.dist;
    }
}

//描画
void Goal::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Goal::Release()
{
}