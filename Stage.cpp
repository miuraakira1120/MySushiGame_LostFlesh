#include "Stage.h"
#include "Engine/Model.h"
#include "Goal.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //モデルデータのロード
    //hModel_ = Model::Load("ground2.fbx");
    hModel_ = Model::Load("testStage.fbx");
    assert(hModel_ >= 0);
    //transform_.scale_ = { 20.0f, 20.0f, 20.0f };
    Instantiate<Goal>(this);
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Stage::Release()
{
}