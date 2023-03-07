#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Time.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(-1),fallFlag(false),
    prevPos(0.0f,0.0f,0.0f), pSyari(nullptr),pStage(nullptr), hSyariModel(-1), 
    hGroundModel(-1),vertexBonePos(),pParticle_(nullptr)
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
    hModel_ = Model::Load("Maguro.fbx");
    assert(hModel_ >= 0);

    pParticle_ = Instantiate<Particle>(this);
}

//�X�V
void Maguro::Update()
{
    //�I�u�W�F�N�g��T���āA�|�C���^�ɓ����
    FindAllObject();

    //�e���_�̈ʒu�𒲂ׂ�
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }

    //��ԒႢ�Ƃ���ƍ����Ƃ����T��
    int lowest = 0;
    int highest = 0;
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[lowest].y > vertexBonePos[i].y)
        {
            lowest = i;
        }
        if (vertexBonePos[highest].y < vertexBonePos[i].y)
        {
            highest = i;
        }
    }

    RayCastData nowLowPosData;                    //��ԒႢ�p���烌�C���΂��āA���ƂԂ��邩�𒲂ׂ�
    nowLowPosData.start = { vertexBonePos[lowest].x,vertexBonePos[lowest].y + 3,vertexBonePos[lowest].z };  /*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //���C�̕���
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &nowLowPosData); //���C�𔭎�

    RayCastData nowHightPosData;                    //��ԒႢ�p���烌�C���΂��āA���ƂԂ��邩�𒲂ׂ�
    nowHightPosData.start = vertexBonePos[highest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //���C�̕���
    nowHightPosData.dir = XMFLOAT3(0, -1, 0);       //���C�̕���
    Model::RayCast(hGroundModel, &nowHightPosData); //���C�𔭎�

    if (nowLowPosData.pos.y >= vertexBonePos[lowest].y)
    {
       SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
       pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }

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
    RayCastData rayData;
    rayData.start = start;
    rayData.dir = dir;
    Model::RayCast(hModel, &rayData);
    return rayData;
}

void Maguro::PhysicalOperation()
{
    RayCastData syariData = DoRay(GetParentPos(), XMFLOAT3(0, -1, 0), hSyariModel);

    XMFLOAT3 syariUpDistanceDifference = pSyari->GetUpDistanceDifference();
    //�}�O�����V�����̏�ɏ���Ă�����
    //if (!syariData.hit)
    {
        //�E�Ǝ�O�̂ق�������΁{
        //���̉��ق�������΁|
        if (syariUpDistanceDifference.z > FALL_ANGLE || syariUpDistanceDifference.z < FALL_ANGLE)
        {
            if (syariUpDistanceDifference.z > FALL_ANGLE && FALL_ANGLE > 0)
            {
                transform_.position_.x += FALL_SPEED * abs(syariUpDistanceDifference.z);
            }
            else
            {
                transform_.position_.x -= FALL_SPEED * abs(syariUpDistanceDifference.z);
            }
        }
        if (syariUpDistanceDifference.x > FALL_ANGLE || syariUpDistanceDifference.x < FALL_ANGLE)
        {
            if (syariUpDistanceDifference.x > FALL_ANGLE && FALL_ANGLE > 0)
            {
                transform_.position_.z -= FALL_SPEED * abs(syariUpDistanceDifference.x);
            }
            else
            {
                transform_.position_.z += FALL_SPEED * abs(syariUpDistanceDifference.x);
            }
        }
    }

    if (abs(transform_.position_.x) > SYARI_SIZE_X || abs(transform_.position_.z) > SYARI_SIZE_Z)
    {

        //�������Ă���
        transform_.position_.y -= 0.1f;
    }
        //���ɃV�������Ȃ�������
}




