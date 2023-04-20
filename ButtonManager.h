#pragma once
#include "Engine/GameObject.h"

namespace ButtonManager
{
    /// <summary>
    /// �{�^���I�u�W�F�N�g�̐����Ə����ݒ�
    /// </summary>
    /// <param name="pParent">�e�I�u�W�F�N�g</param>
    /// <param name="pChild">�q�I�u�W�F�N�g</param>
    /// <param name="position">�����ʒu</param>
    /// <param name="interval">�����Ԋu</param>
    void InstantiateButton(GameObject* pParent, GameObject* pChild, XMFLOAT3& position, const XMFLOAT3& interval);

    //�e�X�g�{�^���̍쐬
    GameObject* CreateTestButton(GameObject* pParent, XMFLOAT3 position);

};

