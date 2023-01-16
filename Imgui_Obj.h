#pragma once
#include "Engine/GameObject.h"
#include "Maguro.h"
#include "Syari.h"
#include "Engine/Text.h"

//imguiを管理するクラス
class Imgui_Obj : public GameObject
{
    Maguro* pMaguro;
    Syari* pSyari;
    Text* pText;

public:
    //コンストラクタ
    Imgui_Obj(GameObject* parent);

    //デストラクタ
    ~Imgui_Obj();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    /// <summary>
    /// オブジェクトを探して入れる関数
    /// </summary>
    void FindAllObject();

    /// <summary>
    /// Imguiの生成
    /// </summary>
    void InstantiateImgui();
};
