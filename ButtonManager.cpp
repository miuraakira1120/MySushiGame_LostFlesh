#include "ButtonManager.h"
#include "ChangeSceneButton.h"

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
        Math::Float3Sub(position, interval);
    }


    //画面遷移ボタンの作成
    GameObject* CreateSceneChangeButton(GameObject* pParent, XMFLOAT3 position, SCENE_ID name, std::string imageName)
    {
        auto* pNewObject = new ChangeSceneButton(pParent, name, imageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }
}