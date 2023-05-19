#include "ButtonManager.h"
#include "ChangeSceneButton.h"

namespace ButtonManager
{
    //�{�^���I�u�W�F�N�g�̐����Ə����ݒ�
    void InstantiateButton(GameObject* pParent, GameObject* pChild, XMFLOAT3& position, const XMFLOAT3& interval)
    {
        if (pParent != nullptr)
        {
            pParent->PushBackChild(pChild);
        }

        //����������
        pChild->Initialize();
        //�����ʒu����
        pChild->SetPosition(position);

        //�Ԋu���󂯂�
        Math::Float3Sub(position, interval);
    }


    //��ʑJ�ڃ{�^���̍쐬
    GameObject* CreateSceneChangeButton(GameObject* pParent, XMFLOAT3 position, SCENE_ID name, std::string imageName)
    {
        auto* pNewObject = new ChangeSceneButton(pParent, name, imageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }
}