#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Syari.h"
#include "Maguro.h"
#include "Engine/Direct3D.h"

//�R���X�g���N�^
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller")
{
}

//�f�X�g���N�^
Controller::~Controller()
{
}

//������
void Controller::Initialize()
{
    transform_.position_ = { 7, 0, 7 };
    XMFLOAT3 fCam = { 7, 10, -10 };
    Camera::SetPosition(fCam);
}

//�X�V
void Controller::Update()
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //�J�����̏œ_��Controller�I�u�W�F�N�g��
    Camera::SetTarget(transform_.position_);
    //A�L�[����������J�����Əœ_�����ɓ���
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= 0.1;
    }
    //D�L�[����������J�����Əœ_���E�ɓ���
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += 0.1;
    }
    //W�L�[����������J�����Əœ_�����ɓ���
    if (Input::IsKey(DIK_W))
    {
        transform_.position_.z += 0.1;
    }
    //S�L�[����������J�����Əœ_����O�ɓ���
    if (Input::IsKey(DIK_S))
    {
        transform_.position_.z -= 0.1;
    }

    //���L�[�ŉ�]
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y += CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y -= CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_UP))
    {
        transform_.rotate_.x += CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_DOWN))
    {
        transform_.rotate_.x -= CAMERA_SPEED;
    }
    XMVECTOR vCam = XMVectorSet(0.0f, 8.0f, -5.0f, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);

    Camera::SetPosition(camPos);
    Syari* pSyari = (Syari*)FindObject("Syari");
    Maguro* pMaguro = (Maguro*)FindObject("Maguro");
    transform_.position_ = pSyari->GetPosition();

    Camera::SetTarget(transform_.position_);
}

//�`��
void Controller::Draw()
{
}

//�J��
void Controller::Release()
{
}

XMFLOAT3 Controller::GetPosition()
{
    return transform_.position_;
}