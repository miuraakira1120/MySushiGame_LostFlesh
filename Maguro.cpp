#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"


//�R���X�g���N�^
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(-1),fallFlag(false)
{
}

//�f�X�g���N�^
Maguro::~Maguro()
{
}

//������
void Maguro::Initialize()
{
    //transform_.position_.x = 2.0f;
    transform_.position_.y = 0.75;

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("maguro.fbx");
    assert(hModel_ >= 0);

    //transform_.position_.x = 3;
}

//�X�V
void Maguro::Update()
{
    Syari* pSyari = (Syari*)FindObject("Syari");    //Syari�I�u�W�F�N�g��T��
    int hSyariModel = pSyari->GetModelHandle();    //���f���ԍ����擾
    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾
    
    ////�X�y�[�X�L�[��������Ă�����
    //if (Input::IsKey(DIK_A))
    //{
    //    //���炩�̏���
    //    transform_.position_.x -= 0.2;
    //}
    //if (Input::IsKey(DIK_D))
    //{
    //    //���炩�̏���
    //    transform_.position_.x += 0.2;
    //}

    RayCastData stageRay;
    stageRay.start = GetParentPos();         //���C�̔��ˈʒu
    //data.start.y = 0;
    stageRay.dir = XMFLOAT3(0, -1, 0);       //���C�̕���

    RayCastData syariRay;
    syariRay.start = GetParentPos();         //���C�̔��ˈʒu
    //data1.start.y = 0;
    syariRay.dir = XMFLOAT3(0, -1, 0);       //���C�̕���

    Model::RayCast(hGroundModel, &stageRay); //���C�𔭎�
    Model::RayCast(hSyariModel, &syariRay);  //���C�𔭎�

    //���ɃV�������Ȃ�������
    if (!syariRay.hit)
    {
        fallFlag = true;
        //transform_.rotate_ = GetParent()->GetRotate();
        //�Ȃ񂩂��낢�돈������
        //transform_.rotate_.z -= 0.25;
        transform_.position_.y -= 0.01;

        //transform_.rotate_ = Transform::Float3Reverse((GetParent()->GetRotate()));
        transform_.ChangeParentRotate(1);
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

