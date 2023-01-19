#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Time.h"

//�R���X�g���N�^
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(-1),fallFlag(false),
    prevPos(0.0f,0.0f,0.0f), pSyari(nullptr),pStage(nullptr), hSyariModel(0), 
    hGroundModel(0)
{
}

//�f�X�g���N�^
Maguro::~Maguro()
{
}

//������
void Maguro::Initialize()
{
    //�����ʒu�̐ݒ�
    transform_.position_.y = SYARI_SIZE_Y + MAGURO_SIZE_Y;

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("maguro.fbx");
    assert(hModel_ >= 0);

    //�����蔻��̐���
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 0.5f, 3));
    AddCollider(collision);
}

//�X�V
void Maguro::Update()
{
    //�I�u�W�F�N�g��T���āA�|�C���^�ɓ����
    FindAllObject();

    //�V�����̕������Z
    PhysicalOperation();
    
    prevPos = transform_.position_;//�����̍��̏ꏊ��1f�O�̏ꏊ�ϐ��ɓ����
}

//�`��
void Maguro::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Maguro::Release()
{
}

//�����ɓ�������
void Maguro::OnCollision(GameObject* pTarget)
{ 
}

//�I�u�W�F�N�g��T���āA�|�C���^�ɓ����
void Maguro::FindAllObject()
{
    pSyari = (Syari*)FindObject("Syari");    //Syari�I�u�W�F�N�g��T��
    hSyariModel = pSyari->GetModelHandle();  //���f���ԍ����擾

    pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    hGroundModel = pStage->GetModelHandle(); //���f���ԍ����擾
}

//���C���΂�
RayCastData Maguro::DoRay(XMFLOAT3 start, XMFLOAT3 dir, int hModel)
{
    //RayCastData rayData;
    //rayData.start = GetParentPos();         //���C�̔��ˈʒu
    //rayData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���

    ////RayCastData syariRay;
    ////syariRay.start = GetParentPos();         //���C�̔��ˈʒu
    ////syariRay.dir = XMFLOAT3(0, -1, 0);       //���C�̕���

    //Model::RayCast(hGroundModel, &rayData); //���C�𔭎�
    ////Model::RayCast(hSyariModel, &syariRay);  //���C�𔭎�
    RayCastData rayData;
    rayData.start = start;
    rayData.dir = dir;
    Model::RayCast(hModel, &rayData);
    return rayData;
}

void Maguro::PhysicalOperation()
{
    RayCastData syariData = DoRay(GetParentPos(), XMFLOAT3(0, -1, 0), hSyariModel);
    //���ɃV�������Ȃ�������
    if (!syariData.hit)
    {
        fallFlag = true;
        //transform_.position_.y -= 0.01;
        //transform_.position_.y -= syariData.dist;
        //transform_.ChangeParentRotate(1);
    }

    //�}�O�����V�����̏�ɏ���Ă�����
    if (!fallFlag)
    {
        if ((int)pSyari->GetRotate().z % ROTATE_MAX > FALL_ANGLE)
        {
            transform_.position_.x -= FALL_SPEED * ((int)pSyari->GetRotate().z % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().z % ROTATE_MAX < -FALL_ANGLE)
        {
            transform_.position_.x -= FALL_SPEED * ((int)pSyari->GetRotate().z % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().x % ROTATE_MAX > FALL_ANGLE)
        {
            transform_.position_.z += FALL_SPEED * ((int)pSyari->GetRotate().x % ROTATE_MAX);
        }
        if ((int)pSyari->GetRotate().x % ROTATE_MAX < -FALL_ANGLE)
        {
            transform_.position_.z += FALL_SPEED * ((int)pSyari->GetRotate().x % ROTATE_MAX);
        }
    }
}



