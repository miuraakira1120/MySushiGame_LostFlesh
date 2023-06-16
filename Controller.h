#pragma once
#include "Engine/GameObject.h"

class Controller : public GameObject
{
    const float CAMERA_SPEED = 3.0f;
    const float UP_ANGLE_LIMIT = 1000;
    const float DOWN_ANGLE_LIMIT = -1000;
    const float PAD_SPEED = 3.0f;
    int hPict_;    //画像番号

    XMFLOAT3 cameraDistance;//コントローラーからカメラの距離

    const float MOVED_FOV = XM_PIDIV4 * 1.1f; // プレイヤーが移動している時のFoV
    const float FOV = XM_PIDIV4; // プレイヤーが立ち止まっている時のFoV
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

    /// <summary>
    /// コントローラーでカメラを回転させる関数
    /// </summary>
    /// <param name="position">コントローラーの位置を変える</param>
    void SetCameraPos(XMFLOAT3 position);

    /// <summary>
    /// リープを使用してコントローラーでカメラを回転させる関数
    /// </summary>
    /// <param name="position">到達するべき位置</param>
    /// <param name="attenRate">減衰比率(1{等倍 }より0.1の方が減速する)</param>
    void SetCameraLerpPos(XMFLOAT3 position, float attenRate);

    /// <summary>
    /// リープをとFoV使用してコントローラーでカメラを回転させる関数
    /// 動いていたかどうかによってFoVを変更
    /// </summary>
    /// <param name="isMoved">動いていたか</param>
    void ChangeFovMove(bool isMoved);
};

