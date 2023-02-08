#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Neta : public GameObject
{

public:
    //コンストラクタ
    Neta(GameObject* parent);

    //デストラクタ
    ~Neta();

    //初期化
    virtual void Initialize() = 0;

    //更新
    virtual void Update() = 0;

    //描画
    virtual void Draw() = 0;

    //開放
    virtual void Release() = 0;
};