#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Syari.h"
#include "Maguro.h"
#include "Engine/Direct3D.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller")
{
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
//    transform_.position_ = { 7, -10, 7 };
//    XMFLOAT3 fCam = { 7, 10, -10 };
//    Camera::SetPosition(fCam);
}

//更新
void Controller::Update()
{
    Syari* pSyari = (Syari*)FindObject("Syari");
    Maguro* pMaguro = (Maguro*)FindObject("Maguro");
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //カメラの焦点をControllerオブジェクトに
    //矢印キーで回転
    if (Input::IsKey(DIK_LEFT))
    {
        transform_.rotate_.y -= CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        transform_.rotate_.y += CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_UP) && transform_.rotate_.x > DOWN_ANGLE_LIMIT)
    {
            transform_.rotate_.x -= CAMERA_SPEED; 
    }
    if (Input::IsKey(DIK_DOWN) && transform_.rotate_.x < UP_ANGLE_LIMIT)
    {
            transform_.rotate_.x += CAMERA_SPEED; 
    }
    XMVECTOR vCam = XMVectorSet(0.0f, 4.0f, 10.0f, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    transform_.position_ = pSyari->GetPosition();
    Camera::SetPosition(camPos);
    Camera::SetTarget(transform_.position_);
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}

XMFLOAT3 Controller::GetPosition()
{
    return transform_.position_;
}

XMFLOAT3 Controller::GetRotate()
{
    return transform_.rotate_;
}
