#include "Ball.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1),fMove(), isPrevRayHit(true)
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
    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

    //��ԉ��̈ʒu���烌�C���΂�
    RayCastData nowLowPosData;                    //��ԒႢ�p���烌�C���΂��āA���ƂԂ��邩�𒲂ׂ�
    nowLowPosData.start = transform_.position_/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //���C�̕���
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &nowLowPosData); //���C�𔭎�

    transform_.position_ = Transform::Float3Add(transform_.position_, fMove);
    //�������ɒn�ʂ���������
    if (nowLowPosData.hit && nowLowPosData.dist - BALL_SIZE_Y > accel)
    {
        //�ڒn�t���O���U�ɂ���
        isGround = false;

        //�d��
        if (SPEED_LIMIT >= accel)
        {
            accel += FALL_SPEED;
            transform_.position_.y -= accel;
        }
        else
        {
            transform_.position_.y -= SPEED_LIMIT;
        }
    }
    else if(isPrevRayHit) //�������ɒn�ʂ��Ȃ�������
    {
        accel = 0.0f;
        transform_.position_.y -= nowLowPosData.dist - BALL_SIZE_Y;
        //�ڒn�t���O��^�ɂ���
        isGround = true;
    }

   isPrevRayHit = nowLowPosData.hit;

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
