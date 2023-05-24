#pragma once

class SceneManager;

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
    /// Imguiの生成
    /// </summary>
    void InstantiateImgui();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
};
