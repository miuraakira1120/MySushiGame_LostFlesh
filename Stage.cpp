#include "Stage.h"
#include "Engine/Model.h"
#include "Goal.h"

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
    assert(hModel_ >= 0);
    //transform_.scale_ = { 20.0f, 20.0f, 20.0f };
    Instantiate<Goal>(this);
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