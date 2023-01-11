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


using std::vector;

//�R���X�g���N�^
Syari::Syari(GameObject* parent)
    :GameObject(parent, "Syari"), hModel_(-1), mode(1),axisPos(0.5f, 0.5f, 1.0f)
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
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
    AddCollider(collision);

}

//�X�V
void Syari::Update()
{
    //�L�[���͂�����
    KeyOperation();
    
    if (mode == 0)
    {
        transform_.MoveAxisRotate();
    }
    else
    {
        transform_.NomalAxisRotate();
    }
    transform_.SetAxisTrans(axisPos);
    Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
    int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

    XMMATRIX m =
        XMMatrixTranslation(axisPos.x, axisPos.y, axisPos.z) *
        XMMatrixRotationZ(XMConvertToRadians((int)transform_.rotate_.z % 360)) *
        XMMatrixRotationY(XMConvertToRadians((int)transform_.rotate_.y % 360)) *
        XMMatrixRotationX(XMConvertToRadians((int)transform_.rotate_.x % 360)) *
        XMMatrixTranslation(-(axisPos.x), -(axisPos.y), -(axisPos.z));//����rotate_�x��]������s��
    XMFLOAT3 fRotate = { 0,0,0 };

    
    RedBox* pRedBox = (RedBox*)FindObject("RedBox");    //RedBox�����i��ԉ��̒��_�Ɂj
    BlueBox* pBlueBox = (BlueBox*)FindObject("BlueBox");//BlueBox�����itransform_.position�Ɂj

    vector<XMVECTOR> v;
    for (int i = 0; i < vVertexPos.size(); i++)
    {
        v.push_back(XMVector3TransformCoord(vVertexPos[i], m ));
    }
    XMVECTOR vAxis = XMLoadFloat3(&axisPos);
    XMVECTOR vPos = XMLoadFloat3(&transform_.rotate_);
    XMVector3TransformCoord(vPos, XMMatrixRotationAxis(vAxis, XMConvertToRadians(90)));
    XMStoreFloat3(&transform_.rotate_, vPos);

    float lowest = 0;
    float highest = 0;
    for (int i = 1; i < v.size(); i++)
    {
        if ( XMVectorGetY(v[lowest]) > XMVectorGetY(v[i]))
        {
            lowest = i;
        }
        if (XMVectorGetY(v[highest]) < XMVectorGetY(v[i]))
        {
            highest = i;
        }
    }

    //��ԒႢ�p��position
    XMFLOAT3 lowestPos = {
        XMVectorGetX(v[lowest]) + transform_.position_.x,
        XMVectorGetY(v[lowest]) + transform_.position_.y,
        XMVectorGetZ(v[lowest]) + transform_.position_.z
    };
    //��ԍ����p��position
    XMFLOAT3 highestPos = {
        XMVectorGetX(v[highest]) + transform_.position_.x,
        XMVectorGetY(v[highest]) + transform_.position_.y,
        XMVectorGetZ(v[highest]) + transform_.position_.z
    };

    RayCastData lowestData;
    lowestData.start = lowestPos;   //���C�̔��ˈʒu
    lowestData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &lowestData); //���C�𔭎�

    float upPos = 0;
    //���C������������
    if (lowestData.hit)
    {
        transform_.position_.y -= 0.1;
    }
    else
    {
        RayCastData posData;
        posData.start = transform_.position_;   //���C�̔��ˈʒu
        posData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
        Model::RayCast(hGroundModel, &posData); //���C�𔭎�
        float distance = abs(lowestPos.y) + abs(transform_.position_.y);//��ԒႢ�p�ƈ�ԍ����p�̋��������߂�
        upPos = distance - posData.dir.y ;
    }

    if (breakFlag)
    {
        int a = 0;
    }

    transform_.position_.y += upPos;
    pRedBox->SetPosition(highestPos);
    pBlueBox->SetPosition(transform_.position_);

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
        transform_.rotate_.x += 0.3f;
    }
    //S�L�[���������Ƃ�
    if (Input::IsKey(DIK_S))
    {
        transform_.rotate_.x -= 0.3f;
    }
}

