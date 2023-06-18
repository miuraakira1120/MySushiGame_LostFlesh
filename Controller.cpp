#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Syari.h"
#include "Maguro.h"
#include "Engine/Direct3D.h"
#include "Engine/Image.h"

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller"), hPict_(-1), cameraDistance(0.0f, 4.0f, 20.0f)
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

//コントローラーでカメラを回転関数
void Controller::SetCameraPos(XMFLOAT3 position)
{
    //現在地をXMVECTORに変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //カメラの位置の設定
    //距離を設定
    XMVECTOR vCam = XMVectorSet(cameraDistance.x, cameraDistance.y, cameraDistance.z, 0.0f);

    //コントローラーの角度によってカメラの位置を変える
    XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vCam = XMVector3TransformCoord(vCam, mRotate);
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vPos + vCam);
    transform_.position_ = position;
    
    //カメラの位置を変える
    Camera::SetPosition(camPos);

    //カメラの焦点を変える
    Camera::SetTarget(transform_.position_);
}

//リープを使用してコントローラーでカメラを回転させる関数
void Controller::SetCameraLerpPos(XMFLOAT3 position, float attenRate)
{
    //XMVECTORに変換
    //到達するべき位置
    XMVECTOR vReachPosition = XMLoadFloat3(&position);

    //現在地
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //Lerp減衰
    XMVECTOR vCamPos = XMVectorLerp(vPos, vReachPosition, attenRate);

    //XMFLOAT3に変換
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vCamPos);

    //コントローラーでカメラを回転
    SetCameraPos(camPos);
}
//リープとFoV使用してコントローラーでカメラを回転させる関数
void Controller::ChangeFovMove(bool isMoved)
{
    //FoVの設定
    float fov = isMoved ? MOVED_FOV : FOV;
    Camera::SetFOV(fov);
}
