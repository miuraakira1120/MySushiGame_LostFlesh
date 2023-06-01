#pragma once
#include "Engine/GameObject.h"

//画像を出すだけのクラス
class ImageBase : public GameObject
{
    int hPict_;                //画像番号
    std::string PrevPathName_; //1フレーム前の画像番号

public:
    //コンストラクタ
    ImageBase(GameObject* parent, std::string pathName, int alpha = 255);

    //デストラクタ
    ~ImageBase();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};