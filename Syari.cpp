#include <DirectXMath.h>

#include <vector>
#include "Syari.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "RedBox.h"
#include "BlueBox.h"
#include "Engine/Camera.h"
#include "Maguro.h"
#include <directxmath.h>
#include "Engine/BoxCollider.h"
#include "Goal.h"
#include "Controller.h"
#include "Time.h"

#include <map>

using std::vector;

//�R���X�g���N�^
Syari::Syari(GameObject* parent)
    :GameObject(parent, "Syari"), hModel_(-1), mode(1), axisPos(0.5f, 0.5f, 1.0f),
    prevPos(0.0f, 0.0f, 0.0f), accel(1.0f), jumpSpeed(0), pGauge_(nullptr),isGround(false)
{
}

//�f�X�g���N�^
Syari::~Syari()
{
}

//������
void Syari::Initialize()
{
    //���f���f�[�^�̃��[�h
    //hModel_ = Model::Load("syari.fbx");
    hModel_ = Model::Load("syari.fbx");
    assert(hModel_ >= 0);

    //���_�̍��W��vVertexPos�ɓ����
    vVertexPos.push_back(upRightFrontPos);
    vVertexPos.push_back(upRightBackPos);
    vVertexPos.push_back(upLeftFrontPos);
    vVertexPos.push_back(upLeftBackPos);
    vVertexPos.push_back(downRightFrontPos);
    vVertexPos.push_back(downRightBackPos);
    vVertexPos.push_back(downLeftFrontPos);
    vVertexPos.push_back(downLeftBackPos);

    //�q�I�u�W�F�N�g�̐���
    Instantiate<Maguro>(this);

    //�����蔻��̐���
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 2));
    AddCollider(collision);

    transform_.position_.y = 40;

    pGauge_ = Instantiate<Gauge>(this);
}

//�X�V
void Syari::Update()
{
    //�L�[���͂�����
    KeyOperation();

    //�e���_�̈ʒu�𒲂ׂ�
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }

    //transform_.SetAxisTrans(axisPos);
    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

    Goal* pGoal = (Goal*)FindObject("Goal");        //�S�[���I�u�W�F�N�g��T��
    int hGoalModel = pGoal->GetModelHandle();       //���f���ԍ����擾

    //XMMATRIX m =
    //    XMMatrixTranslation(axisPos.x, axisPos.y, axisPos.z) *
    //    XMMatrixRotationZ(XMConvertToRadians((int)transform_.rotate_.z % 360)) *
    //    XMMatrixRotationY(XMConvertToRadians((int)transform_.rotate_.y % 360)) *
    //    XMMatrixRotationX(XMConvertToRadians((int)transform_.rotate_.x % 360)) *
    //    XMMatrixTranslation(-(axisPos.x), -(axisPos.y), -(axisPos.z));//����rotate_�x��]������s��
    //XMFLOAT3 fRotate = { 0,0,0 };
    //vector<XMVECTOR> v;
    //for (int i = 0; i < vVertexPos.size(); i++)
    //{
    //    v.push_back(XMVector3TransformCoord(vVertexPos[i], m ));
    //}
    //XMVECTOR vAxis = XMLoadFloat3(&axisPos);
    //XMVECTOR vPos = XMLoadFloat3(&transform_.rotate_);
    //XMVector3TransformCoord(vPos, XMMatrixRotationAxis(vAxis, XMConvertToRadians(90)));
    //XMStoreFloat3(&transform_.rotate_, vPos);
    //float lowest = 0;
    //float highest = 0;
    //for (int i = 1; i < v.size(); i++)
    //{
    //    if ( XMVectorGetY(v[lowest]) > XMVectorGetY(v[i]))
    //    {
    //        lowest = i;
    //    }
    //    if (XMVectorGetY(v[highest]) < XMVectorGetY(v[i]))
    //    {
    //        highest = i;
    //    }
    //}
    ////��ԒႢ�p��position
    //XMFLOAT3 lowestPos = {
    //    XMVectorGetX(v[lowest]) + transform_.position_.x,
    //    XMVectorGetY(v[lowest]) + transform_.position_.y,
    //    XMVectorGetZ(v[lowest]) + transform_.position_.z
    //};
    ////��ԍ����p��position
    //XMFLOAT3 highestPos = {
    //    XMVectorGetX(v[highest]) + transform_.position_.x,
    //    XMVectorGetY(v[highest]) + transform_.position_.y,
    //    XMVectorGetZ(v[highest]) + transform_.position_.z
    //};
    //RayCastData lowestData;                     //��ԒႢ�p���烌�C���΂��āA���ƂԂ��邩�𒲂ׂ�
    //lowestData.start = lowestPos;               //���C�̔��ˈʒu
    //lowestData.dir = XMFLOAT3(0, -1, 0);        //���C�̕���
    //Model::RayCast(hGroundModel, &lowestData);  //���C�𔭎�
    ////���C������������
    //if (lowestData.hit)
    //{
    //}
    //else
    //{
    //    //RayCastData posData;
    //    //posData.start = transform_.position_;   //���C�̔��ˈʒu
    //    //posData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    //    //Model::RayCast(hGroundModel, &posData); //���C�𔭎�
    //    //float distance = abs(lowestPos.y) + abs(transform_.position_.y);//��ԒႢ�p�ƈ�ԍ����p�̋��������߂�
    //}
    //RedBox* pRedBox = (RedBox*)FindObject("RedBox");    //RedBox��T���i��ԉ��̒��_�Ɂj
    //BlueBox* pBlueBox = (BlueBox*)FindObject("BlueBox");//BlueBox��T���itransform_.position�Ɂj
    //pRedBox->SetPosition(highestPos);
    //pBlueBox->SetPosition(transform_.position_);

    ////////////////////���C���΂�/////////////////////
    
    RayCastData GoalData;                       //�V�����̈ʒu���烌�C���΂��āA�S�[���ƂԂ��邩�𒲂ׂ�
    GoalData.start = transform_.position_;      //���C�̔��ˈʒu
    GoalData.dir = XMFLOAT3(0, -1, 0);          //���C�̕���
    Model::RayCast(hGoalModel, &GoalData);      //���C�𔭎�

    RayCastData prevPosData;                    //��ԒႢ�p���烌�C���΂��āA���ƂԂ��邩�𒲂ׂ�
    prevPosData.start = prevPos/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //���C�̕���
    prevPosData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &prevPosData); //���C�𔭎�

    RayCastData nowPosData[6];
    for (int i = 0; i < sizeof(direction) / sizeof(XMFLOAT3); i++)
    {
        //��ԒႢ�p���烌�C���΂��āA���ƂԂ��邩�𒲂ׂ�
        nowPosData[i].start = XMFLOAT3(transform_.position_.x, transform_.position_.y + directionDistance[i], transform_.position_.z);    //���C�̔��ˈʒu
        nowPosData[i].dir = direction[i];        //���C�̕���
        Model::RayCast(hGroundModel, &nowPosData[i]);  //���C�𔭎�
    }
    // ///////////////////////////////////////////////////

    for (int i = LEFT; i < DIRECTION_MAX; i++)
    {
        if (nowPosData[i].hit && nowPosData[i].dist >= FALL_SPEED)
        {

        }
    }

    //�������ɒn�ʂ���������
    if (nowPosData[BOTOM].hit && nowPosData[BOTOM].dist >= FALL_SPEED)
    {
        //�ڒn�t���O��^�ɂ���
        isGround = false;
        //�d��
        if (FALL_SPEED * (accel - jumpSpeed) <= SPEED_LIMIT)
        {
            Time::UnLock();
            accel += ACCELERATION;
            transform_.position_.y -= FALL_SPEED * (accel - jumpSpeed);
        }
        else
        {
            transform_.position_.y -= FALL_SPEED;
        }
    }
    else //�������ɒn�ʂ��Ȃ�������
    {
        accel = 0.0f;

        Time::Lock();
        transform_.position_.y -= prevPosData.dist - SYARI_SIZE_Y;
        
        //�ڒn�t���O��^�ɂ���
        isGround = true;
    }

    //�S�[��������
    if (GoalData.hit)
    {
        transform_.position_.y = 10000;
    }

    //�������O�̈ʒu��ۑ����Ă���
    prevPos = transform_.position_;
}

//�`��
void Syari::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Syari::Release()
{
}

//���ݒn�̃Q�b�^�[
XMFLOAT3 Syari::GetPosition()
{
    return transform_.position_;
}

//��]�̃Q�b�^�[
XMFLOAT3 Syari::GetRotate()
{
    return transform_.rotate_;
}

//�L�[����
void Syari::KeyOperation()
{
    //SPACE�L�[���������Ƃ�
    if (Input::IsKey(DIK_SPACE))
    {
        breakFlag = true;
    }
    //ENTER�L�[���������Ƃ�
    if (Input::IsKeyDown(DIK_RETURN))
    {
        switch (mode)
        {
        case 0:
            mode += 1;
            break;
        case 1:
            mode -= 1;
            break;
        default:
            break;
        }
    }
    ////////�ړ�/////////////
    //A�L�[���������Ƃ�
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.z += 0.3f;
    }
    //D�L�[���������Ƃ�
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.z -= 0.3f;
    }
    //W�L�[���������Ƃ�
    if (Input::IsKey(DIK_W))
    {
        //�V�����̌���
        //syariDir.z += 90;
        //transform_.position_.z += SYARI_SPEED;
       //transform_.rotate_.x += 0.3f;
        Controller* pController = (Controller*)FindObject("Controller");
        transform_.rotate_.y = pController->GetRotate().y;
        XMFLOAT3 move = { 0,0,0.1f };//�v���C���[�̈ړ��x�N�g��
        XMVECTOR vMove = XMLoadFloat3(&move);//�ړ��x�N�g���̌^��XMVECTOR�ɕϊ�
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        vMove = XMVector3TransformCoord(vMove, mRotate);
        XMVECTOR vPos;
        vPos = XMLoadFloat3(&transform_.position_);//�V�����̌��ݒn��XMVECTOR�ɕϊ�
        vPos -= vMove * 3;
        XMStoreFloat3(&transform_.position_, vPos);//���ݒn��transform_.position_�ɑ���
    }
    //S�L�[���������Ƃ�
    if (Input::IsKey(DIK_S))
    {
    }
}

bool Syari::isFly()
{
    return false;
}

void Syari::Jump()
{
    if (true)
    {

    }
}

