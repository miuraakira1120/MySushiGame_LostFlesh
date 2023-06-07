#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Engine/GameObject.h"
#include "Engine/Direct3D.h"

using namespace DirectX;

class PlayerBase : public GameObject
{
private:
    //定数
    const float FALL_SPEED_LIMIT = 0.5f;    //落下の速度限界 
    const float SPEED_OF_JUMP = 0.4f;       //跳躍速度
    const float FALL_SPEED = 0.02f;         //落ちるスピード
    const float SYARI_SPEED = 0.25f;        //シャリのスピード

    //プレイヤーのサイズ
    const XMFLOAT3 PLAYER_SIZE{
        0.5f,        //シャリのXのサイズ（1倍）
        0.5f,        //シャリのYのサイズ（1倍）
        1.0f,        //シャリのZのサイズ（1倍）
    };

    static const int   DIRECTION_ARRAY_SIZE = 3;   //方向が格納された配列のサイズ

    int   hModel_;               //モデル番号
    bool  isGround;              //地面に設置しているか
    float gravity;               //今受けている重力の力(マイナスなら重力を振り切って上に行く)
    bool  canMove;               //動くことができるか
    XMFLOAT3 size;               //プレイヤーのサイズ
    Direct3D::SHADER_TYPE type;  //描画に使用するシェーダー

public:

    //コンストラクタ
    PlayerBase(GameObject* parent, std::string name, std::string pathName);

    //初期化
    virtual void Initialize() {};

    //更新
    virtual void Update() {};

    //描画
    virtual void Draw();

    //開放
    virtual void Release() {};

    //何かに当たった
   //引数：pTarget 当たった相手
    virtual void OnCollision(GameObject* pTarget) {};

    //ジャンプする
    void Jump();

    /// <summary>
    /// 移動する関数
    /// </summary>
    /// <param name="isInverse">バックするかどうか</param>
    void Move(bool isInverse = false);

    //空中にいるかどうか調べる関数
    bool isFly();

    //モデルのゲッター
    int GetModelHandle() { return hModel_; }

    //重力の処理
    void Gravity();

    /// <summary>
    /// 衝突しているか調べる
    /// </summary>
    /// <param name="hStageModel">ステージのモデル</param>
    /// <param name="vec">レイを飛ばす方法</param>
    /// <param name="length">戻す距離</param>
    /// <returns>衝突したかどうか</returns>
    bool CheckIfCollided(int hStageModel, XMFLOAT3 vec, float &length);
};

