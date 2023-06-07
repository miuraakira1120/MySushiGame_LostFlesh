#include "PlayerBase.h"
#include "Controller.h"
#include "OBB.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"


//�R���X�g���N�^
PlayerBase::PlayerBase(GameObject* parent, std::string name, std::string modelFilename)
    :GameObject(parent, name, modelFilename),hModel_(-1), isGround(false), gravity(0.0f), canMove(true), size(PLAYER_SIZE)
{
}

//�`��
void PlayerBase::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�W�����v
void PlayerBase::Jump()
{
    //���ɂ��Ă�����
    if (isGround)
    {
        gravity -= SPEED_OF_JUMP;
    }
}

//�ړ�����֐�
void PlayerBase::Move(bool isInverse)
{
    //�J�����̃R���g���[���[��T��
    Controller* pController = (Controller*)FindObject("Controller");

    //�J�����̌����ɂ��̃I�u�W�F�N�g��ݒ肷��
    transform_.rotate_.y = pController->GetRotate().y;

    //�v���C���[�̈ړ��x�N�g��
    XMFLOAT3 move = { 0,0,SYARI_SPEED };

    //�ړ��x�N�g���̌^��XMVECTOR�ɕϊ�
    XMVECTOR vMove;
    vMove = XMLoadFloat3(&move);

    //�ړ���������ɉ�]
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vMove = XMVector3TransformCoord(vMove, mRotate);

    //�o�b�N�ɂ���Ȃ�move���t�ɂ���
    if (!isInverse)
    {
        vMove *= -1;
    }

    //vMove��XMFLOAT3�ɕϊ�
    XMFLOAT3 fMove;
    XMStoreFloat3(&fMove, vMove);

    //�V�����̌��ݒn��XMVECTOR�ɕϊ�
    XMVECTOR vPos;
    vPos = XMLoadFloat3(&transform_.position_);

    //�ړ���̍��W���v�Z
    vPos += vMove;

    //���ݒn��transform_.position_�ɑ���
    XMStoreFloat3(&transform_.position_, vPos);
}

//�d�͂̏���
void PlayerBase::Gravity()
{
    //�X�s�[�h�̏���ɒB���Ă��Ȃ����
    if (FALL_SPEED_LIMIT >= gravity)
    {
        gravity += FALL_SPEED;
        transform_.position_.y -= gravity;
    }
    else
    {
        transform_.position_.y -= FALL_SPEED_LIMIT;
    }
}

//�Փ˂��Ă��邩���ׂ�
bool PlayerBase::CheckIfCollided(int hStageModel, XMFLOAT3 vec, float& length)
{
    //�V�����̌��ݒn��XMVECTOR�ɕϊ�
    XMVECTOR vPos;
    vPos = XMLoadFloat3(&transform_.position_);

    //OBB�Ɏg�p����x�N�g���̌����쐬
    XMFLOAT3 fBoneDir[DIRECTION_ARRAY_SIZE] =
    {
        {size.x, 0, 0},
        {0, size.y, 0},
        {0, 0, size.z},
    };

    //OBB�Ɏg�p����x�N�g�����쐬
    //DIRECTION�̕����[�v����
    std::vector<XMVECTOR> dirVec;
    for (int i = 0; i < DIRECTION_ARRAY_SIZE; i++)
    {
        //fBoneDir��XMVECTOR�ɕϊ�
        XMVECTOR vBoneDir = XMLoadFloat3(&fBoneDir[i]);

        //BoneDir���s�񂍂ŕό`
        vBoneDir = XMVector3TransformCoord(vBoneDir, transform_.changeMatRotate_);	

        //vBoneDir�Ƀ|�W�V�����𑫂�
        vBoneDir += vPos;

        //XMFLOAT�ɒ���
        XMStoreFloat3(&fBoneDir[i], vBoneDir);

        //���X�g�ɒǉ�����
        dirVec.push_back(vBoneDir - vPos);
    }

    //OBB�Ɏg�p����x�N�g���̒������擾
    std::vector<float> fLength;
    for (int i = 0; i < fLength.size() - 1; i++)
    {
        //���X�g�ɒǉ�����
        fLength.push_back(XMVectorGetX(XMVector3Length(dirVec[i])));
    }

    //�v���C���[��OBB��ݒ�
    OBB prayerOBB;
    prayerOBB.SetOBBAll(vPos, dirVec, fLength);

    //����OBB�Փ˔���
    RayCastData prayerOBBData;
    prayerOBBData.start = transform_.position_;   //���C�̔��ˈʒu
    prayerOBBData.dir = vec;                      //���C�̕���
    Model::RayCast(hStageModel, &prayerOBBData);  //���C�𔭎�

    float len;
    //���C���������Ă��āA�Փ˂��Ă�����
    if (prayerOBBData.hit && prayerOBB.OBBvsPlane(prayerOBB, prayerOBBData.pos, prayerOBBData.normal, &len))
    {
        length = len;
        return TRUE;
    }
    return FALSE;
}
