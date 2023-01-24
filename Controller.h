#pragma once
#include "Engine/GameObject.h"

class Controller : public GameObject
{
    const float CAMERA_SPEED = 1.5f;
    const float UP_ANGLE_LIMIT = 30;
    const float DOWN_ANGLE_LIMIT = -45;
public:
    //コンストラクタ
    Controller(GameObject* parent);

    //デストラクタ
    ~Controller();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //現在位置のゲッター
    XMFLOAT3 GetPosition();

    //向きのゲッター
    XMFLOAT3 GetRotate();
    XMFLOAT3 GetCameraPos();
};

