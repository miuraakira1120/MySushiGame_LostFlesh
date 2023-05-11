#pragma once
#include "Engine/GameObject.h"
#include "Maguro.h"
#include "Syari.h"
#include "Engine/Text.h"
#include "ChangeSceneButton.h"
#include "Engine/SceneManager.h"

//imguiを管理するクラス
namespace Imgui_Obj
{
    //初期化
    void Initialize(SceneManager* pSceneManager_);

    //更新
    void Update();

    //開放
    void Release();

    /// <summary>
    /// オブジェクトを探して入れる関数
    /// </summary>
    void FindAllObject();

    /// <summary>
    /// Imguiの生成
    /// </summary>
    void InstantiateImgui();
};
