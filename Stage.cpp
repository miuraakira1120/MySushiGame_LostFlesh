#include "Stage.h"
#include "Engine/Model.h"
#include "Goal.h"
#include "SalmonRoe.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //���f���f�[�^�̃��[�h
    //hModel_ = Model::Load("ground2.fbx");
    hModel_ = Model::Load("testStage.fbx");
    hModel_ = Model::Load("stage1-1TrueTest.fbx");
    assert(hModel_ >= 0);
    //transform_.position_.y = -5;
    //transform_.scale_ = { 20.0f, 20.0f, 20.0f };
    Instantiate<Goal>(this);

    XMFLOAT3 setPos[4] =
    {
        {-30, 13, 139},
        {-5, 13, 139},
        {11,13,139},
        {27,13,138.7}
    };

    for (int i = 0; i < 4; i++)
    {
        SalmonRoe* pSalmonRoe = Instantiate<SalmonRoe>(this);
        pSalmonRoe->SetPosition(setPos[i]);
        pSalmonRoe->SetRotate(0,270,0);
    }

    Goal* pGoal = Instantiate<Goal>(this);
    pGoal->SetPosition(4.5, 13, 285);
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{
}