#pragma once
#include "Engine/GameObject.h"
#include <vector>

#define VERTEX_VLU 8

const float SYARI_SIZE_X = 0.5f; //シャリのXのサイズ（1倍）
const float SYARI_SIZE_Y = 0.5f; //シャリのYのサイズ（1倍）
const float SYARI_SIZE_Z = 1.0f; //シャリのZのサイズ（1倍）

using std::vector;



class Syari : public GameObject
{

    enum Ver
    {
        UP_RIGHT_FRONT = 0,
        UP_RIGHT_BACK,
        UP_LEFT_FRONT,
        UP_LEFT_BACK,
        DOWN_RIGHT_FRONT,
        DOWN_RIGHT_BACK,
        DOWN_LEFT_FRONT,
        DOWN_LEFT_BACK,

    };
    
   
    const float ROTATE_SPEED = 0.5f; //シャリの回転のスピード
    const float FALL_SPEED   = 0.1f; //落ちるスピード

    const XMVECTOR upRightFrontPos =   { 0.5f, 0.5f, 1.0f    };//シャリの上右前の位置
    const XMVECTOR upRightBackPos =    { 0.5f, 0.5f, -1.0f   };//シャリの上右後の位置
    const XMVECTOR upLeftFrontPos =    { -0.5f, 0.5f, 1.0f   };//シャリの上左前の位置
    const XMVECTOR upLeftBackPos =     { -0.5f, 0.5f, -1.0f  };//シャリの上左後の位置
    const XMVECTOR downRightFrontPos = { 0.5f, -0.5f, 1.0f   };//シャリの下左前の位置
    const XMVECTOR downRightBackPos =  { 0.5f, -0.5f, -1.0f  };//シャリの下右後の位置
    const XMVECTOR downLeftFrontPos =  { -0.5f, -0.5f, 1.0f  };//シャリの下左前の位置
    const XMVECTOR downLeftBackPos =   { -0.5f, -0.5f, -1.0f };//シャリの下左後の位置

    vector<XMVECTOR> vVertexPos;
    int hModel_;    //モデル番号
    int mode;     //モード
    bool breakFlag = false;

   

public:
   
    //コンストラクタ
    Syari(GameObject* parent);

    //デストラクタ
    ~Syari();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //positionのゲッター
    XMFLOAT3 GetPosition();

    //rotateのゲッター
    XMFLOAT3 GetRotate();

    int GetModelHandle() { return hModel_; }

    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;
};