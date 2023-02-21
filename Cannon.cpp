#include "Cannon.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Ball.h"

//�R���X�g���N�^
Cannon::Cannon(GameObject* parent)
    :GameObject(parent, "Cannon"), hModel_(-1),timer(0)
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
    hModel_ = Model::Load("Cannon_kari.fbx");
    assert(hModel_ >= 0);

    //Model::SetAnimFrame(hModel_, 1, 3000, 3.0f);

    transform_.rotate_.z = 50.0f;

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
        transform_.position_.y -= data.dist - CANNON_SIZE_Y;
    }
}

//�X�V
void Cannon::Update()
{
    /*XMFLOAT3 CannonFront = Model::GetBonePosition(hModel_, "Cannon_Front");
    XMFLOAT3 CannonBack = Model::GetBonePosition(hModel_, "Cannon_Back");*/
   
    if (timer >=60)
    {
        XMFLOAT3 CannonFront = Transform::Float3Add({ 1.5f,2,0 }, transform_.position_);
        XMFLOAT3 CannonBack = transform_.position_;
            XMVECTOR vCannonFront = XMLoadFloat3(&CannonFront);
            XMVECTOR vCannonBack = XMLoadFloat3(&CannonBack);

            XMFLOAT3 fBallMove;
            XMVECTOR vBallMove = vCannonFront - vCannonBack;
            vBallMove = XMVector3Normalize(vBallMove);
            vBallMove *= 0.5;
            XMStoreFloat3(&fBallMove, vBallMove);

            Ball* pBall = Instantiate<Ball>(this->GetParent());
            pBall->SetPosition(CannonBack);
            pBall->SetMove(fBallMove);

            timer = 0;
    }
    timer++;
   /* Syari* pSyari = (Syari*)FindObject("Syari");
    transform_.position_ = pSyari->GetPosition();*/
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