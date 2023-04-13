#include "ButtonManager.h"

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
        Transform::Float3Sub(position, interval);
    }
}