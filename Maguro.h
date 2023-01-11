#pragma once
#include "Engine/GameObject.h"

class Stage;
class Syari;


class Maguro : public GameObject
{
    const float MAGURO_SIZE_X = 0.25f; //マグロのXのサイズ（1倍）
    const float MAGURO_SIZE_Y = 0.25f; //マグロのYのサイズ（1倍）
    const float MAGURO_SIZE_Z = 1.5f;  //マグロのZのサイズ（1倍）

    const float FALL_ANGLE = 5.0f;    //落ちる角度
    const short ROTATE_MAX = 360;      //回転の最大
    const float FALL_SPEED = 0.2f * 0.01f;     //落ちるスピード

    int hModel_;     //モデル番号
    bool fallFlag;   //マグロが落ちるかどうかフラグ
    Syari* pSyari;   //シャリのポインタ
    int hSyariModel; //シャリのモデル番号
    Stage* pStage;   //ステージのポインタ
    int hGroundModel;//ステージのモデル番号

    XMFLOAT3 pravPos;//1f前の自分の位置
    
public:
    //コンストラクタ
    Maguro(GameObject* parent);

    //デストラクタ
    ~Maguro();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //親の親から見た位置を入手
    XMFLOAT3 GetParentPos()
    {
        return Transform::Float3Add(GetParent()->GetPosition(), transform_.position_);
    }

    //何かに当たった
     //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    
};