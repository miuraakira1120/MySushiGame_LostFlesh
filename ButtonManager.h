#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

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

    /// <summary>
    /// ��ʑJ�ڃ{�^���̍쐬
    /// </summary>
    /// <param name="pParent">�e�I�u�W�F�N�g</param>
    /// <param name="position">�{�^���̈ʒu</param>
    /// <param name="name">�J�ڐ�̖��O</param>
    /// <param name="fileName">�\��������摜�̖��O</param>
    /// <returns>�{�^���̃|�C���^</returns>
    GameObject* CreateSceneChangeButton(GameObject* pParent, XMFLOAT3 position, SCENE_ID name, std::string imageName);
};

