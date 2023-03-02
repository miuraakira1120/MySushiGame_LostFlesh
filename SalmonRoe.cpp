#include "SalmonRoe.h"
#include "Cannon.h"
#include "Engine/Model.h"
#include "Stage.h"

//�R���X�g���N�^
SalmonRoe::SalmonRoe(GameObject* parent)
    :GameObject(parent, "SalmonRoe"), hModel_(-1)
{
}

//�f�X�g���N�^
SalmonRoe::~SalmonRoe()
{
}

//������
void SalmonRoe::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("salmonRoe.fbx");
    assert(hModel_ >= 0);
    Instantiate<Cannon>(this);

    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾
    RayCastData data;
    data.start = transform_.position_;   //���C�̔��ˈʒu
    data.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &data); //���C�𔭎�

     //���C������������
    if (data.hit)
    {
        //���̕��ʒu��������
        transform_.position_.y -= data.dist - SALMONROE_SIZE_Y;
    }

    transform_.position_.x = 4;
}

//�X�V
void SalmonRoe::Update()
{
}

//�`��
void SalmonRoe::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void SalmonRoe::Release()
{
}