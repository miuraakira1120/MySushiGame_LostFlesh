#include "Cannon.h"
#include "Engine/Model.h"
#include "Syari.h"

//�R���X�g���N�^
Cannon::Cannon(GameObject* parent)
    :GameObject(parent, "Cannon"), hModel_(-1)
{
}

//�f�X�g���N�^
Cannon::~Cannon()
{
}

//������
void Cannon::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Cannon.fbx");
    assert(hModel_ >= 0);

    Model::SetAnimFrame(hModel_, 1, 1200, 3.0f);
}

//�X�V
void Cannon::Update()
{
    Syari* pSyari = (Syari*)FindObject("Syari");
    transform_.position_ = pSyari->GetPosition();
}

//�`��
void Cannon::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Cannon::Release()
{
}