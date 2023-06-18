#include "TutorialStage.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "ImageBase.h"

//�R���X�g���N�^
TutorialStage::TutorialStage(GameObject* parent)
    :GameObject(parent, "TutorialStage")
{
}

//�f�X�g���N�^
TutorialStage::~TutorialStage()
{
}

//������
void TutorialStage::Initialize()
{
    hModel_ = Model::Load("Tutorial.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void TutorialStage::Update()
{
    //�v���C���[��T���ă|�W�V�������Q�b�g�i��ŕύX����j
    Syari* pSyari = (Syari*)FindObject("Syari");
    XMFLOAT3 playerPos =  pSyari->GetPosition();

    //�W�����v�̃`���[�g���A���摜�\���i��ŕύX����j
    static bool flag = false;
    if (playerPos.z <= -16.0f && playerPos.z >= -34.0f && flag == false)
    {

        InstantiateImage<ImageBase>(this, "BlackBack.jpg", transform_.position_, transform_.rotate_, XMFLOAT3(0.6f, 0.6, 1.0f), 126);
        flag = true;
    }
}

//�`��
void TutorialStage::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void TutorialStage::Release()
{
}