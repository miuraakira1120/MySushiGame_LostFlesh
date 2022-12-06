#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Stage : public GameObject
{
    int hModel_;    //モデル番号
public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //ハンドルを取得する関数
    int GetModelHandle() { return hModel_; }


};
