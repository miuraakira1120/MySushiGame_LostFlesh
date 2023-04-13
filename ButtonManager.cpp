#include "ButtonManager.h"

namespace ButtonManager
{
    //ボタンオブジェクトの生成と初期設定
    void InstantiateButton(GameObject* pParent, GameObject* pChild, XMFLOAT3& position, const XMFLOAT3& interval)
    {
        if (pParent != nullptr)
        {
            pParent->PushBackChild(pChild);
        }

        //初期化処理
        pChild->Initialize();
        //生成位置調整
        pChild->SetPosition(position);

        //間隔を空ける
        Transform::Float3Sub(position, interval);
    }
}