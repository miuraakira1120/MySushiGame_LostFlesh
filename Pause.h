#pragma once
#include "Engine/GameObject.h"
#include <directxmath.h>

class Transform;

//Pauseシーンを管理するクラス
class Pause
{
private:

public:
    //コンストラクタ
    Pause();

    //デストラクタ
    ~Pause();

    //初期化
    void Initialize();

    //更新
    void Update();

    //描画
    void Draw();

    //開放
    void Release();

};