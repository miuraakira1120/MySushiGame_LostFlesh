#pragma once
#include "Engine/GameObject.h"

//描画を管理するクラス
class DrawManager : public GameObject
{
    //画面分割数
    int screenSeparation;
public:
    //コンストラクタ
    DrawManager(GameObject* parent);

    //デストラクタ
    ~DrawManager();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //ゲッター
    int GetScreenSeparation();

    //セッター
    void SetScreenSeparation(int num);
};