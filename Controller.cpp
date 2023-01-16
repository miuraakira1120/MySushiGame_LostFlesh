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
    transform_.position_ = { 7, 0, 7 };
    XMFLOAT3 fCam = { 7, 10, -10 };
    Camera::SetPosition(fCam);
}

//更新
void Controller::Update()
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //カメラの焦点をControllerオブジェクトに
    Camera::SetTarget(transform_.position_);
    //Aキーを押したらカメラと焦点が左に動く
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= 0.1;
    }
    //Dキーを押したらカメラと焦点が右に動く
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += 0.1;
    }
    //Wキーを押したらカメラと焦点が奥に動く
    if (Input::IsKey(DIK_W))
    {
        transform_.position_.z += 0.1;
    }
    //Sキーを押したらカメラと焦点が手前に動く
    if (Input::IsKey(DIK_S))
    {
        transform_.position_.z -= 0.1;
    }

    //矢印キーで回転
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