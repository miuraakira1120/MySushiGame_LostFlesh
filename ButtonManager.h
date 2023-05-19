#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

namespace ButtonManager
{
    /// <summary>
    /// ボタンオブジェクトの生成と初期設定
    /// </summary>
    /// <param name="pParent">親オブジェクト</param>
    /// <param name="pChild">子オブジェクト</param>
    /// <param name="position">生成位置</param>
    /// <param name="interval">生成間隔</param>
    void InstantiateButton(GameObject* pParent, GameObject* pChild, XMFLOAT3& position, const XMFLOAT3& interval);

    /// <summary>
    /// 画面遷移ボタンの作成
    /// </summary>
    /// <param name="pParent">親オブジェクト</param>
    /// <param name="position">ボタンの位置</param>
    /// <param name="name">遷移先の名前</param>
    /// <param name="fileName">表示させる画像の名前</param>
    /// <returns>ボタンのポインタ</returns>
    GameObject* CreateSceneChangeButton(GameObject* pParent, XMFLOAT3 position, SCENE_ID name, std::string imageName);
};

