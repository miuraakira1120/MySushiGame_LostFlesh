#include "Ball.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1),fMove()
{
}

//�f�X�g���N�^
Ball::~Ball()
{
}

//������
void Ball::Initialize()
{
    hModel_ = Model::Load("Ball.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Ball::Update()
{
    transform_.position_ = Transform::Float3Add(transform_.position_, fMove);
}

//�`��
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
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
