#include "Ball.h"
#include "Engine/Model.h"

//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1),fMove()
{
}

//デストラクタ
Ball::~Ball()
{
}

//初期化
void Ball::Initialize()
{
    hModel_ = Model::Load("Ball.fbx");
    assert(hModel_ >= 0);
}

//更新
void Ball::Update()
{
    transform_.position_ = Transform::Float3Add(transform_.position_, fMove);
}

//描画
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ball::Release()
{
}

void Ball::SetMove(XMFLOAT3 move)
{
    fMove = move;
}

void Ball::SetPosition(XMFLOAT3 pos)
{
    transform_.position_ = pos;
}
