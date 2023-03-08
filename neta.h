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
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};