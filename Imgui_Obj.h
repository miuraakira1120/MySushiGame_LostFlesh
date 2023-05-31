#pragma once
#include "Engine/SceneManager.h"
#include "ButtonManager.h"

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

    /// <summary>
    /// オブジェクトを生成するImguiを出す関数
    /// </summary>
    void ImguiIniObj();

    /// <summary>
    /// シーンチェンジするImguiを生成する関数
    /// </summary>
    void SceneChangeImgui();

    /// <summary>
    /// imguiでボタンを生成した後にやること
    /// </summary>
    void RearButtonInstantiate();
    
    //作ったボタンの再移動等を出来るようにする
    void ReSettingButton();

    /// <summary>
    /// ボタン作成モードの時に出すimgui
    /// </summary>
    void CreateButtonImgui();

    /// <summary>
    /// 画像作成モードの時に出すImgui(Beginの中で使う)
    /// </summary>
    void CreateImageImgui();

    /// <summary>
    /// オブジェクトを生成する時に基本的なImguiを出す(Beginの中で使う)
    /// </summary>
    void SettingBasicImgui();

    /// <summary>
    /// 拡張子を追加する関数(変数extensionを参照)
    /// </summary>
    /// <returns>返す拡張子</returns>
    std::string AddExtension();

};
