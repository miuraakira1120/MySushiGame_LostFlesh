#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Syari.h"
#include "Maguro.h"
#include "Engine/Direct3D.h"
#include "Engine/Image.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller"), hPict_(-1)
{
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
    //画像データのロード
    hPict_ = Image::Load("water.png");
    assert(hPict_ >= 0);
}

//更新
void Controller::Update()
{
    //カメラの焦点をControllerオブジェクトに
    //矢印キーで回転
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_S) && transform_.rotate_.x > DOWN_ANGLE_LIMIT)
    {
        transform_.rotate_.x -= CAMERA_SPEED; 
    }
    if (Input::IsKey(DIK_W) && transform_.rotate_.x < UP_ANGLE_LIMIT)
    {
        transform_.rotate_.x += CAMERA_SPEED; 
    }

    XMFLOAT3 stickR = { Input::GetPadStickR().y, Input::GetPadStickR().x, 0 };
    transform_.rotate_ = Math::Float3Add(Math::Float3Mul( stickR, PAD_SPEED, PAD_SPEED, PAD_SPEED), transform_.rotate_);

    Camera::SetTarget(transform_.position_);
}

//描画
void Controller::Draw()
{
    if (Direct3D::lrMode == 1)
    {
        Image::SetTransform(hPict_, transform_);
        Image::Draw(hPict_);
    }
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

XMFLOAT3 Controller::GetCameraPos(XMFLOAT3 position)
{
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    XMVECTOR vCam = XMVectorSet(0.0f, 4.0f, 10.0f, 0.0f);
    XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    transform_.position_ = position;
    return camPos;
}
