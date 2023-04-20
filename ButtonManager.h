#pragma once
#include "Engine/GameObject.h"

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

    //テストボタンの作成
    GameObject* CreateTestButton(GameObject* pParent, XMFLOAT3 position);

};

