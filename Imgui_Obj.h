#pragma once

#include "Engine/SceneManager.h"
#include "ButtonManager.h"

//imgui���Ǘ�����N���X
namespace Imgui_Obj
{
    //������
    void Initialize(SceneManager* pSceneManager_);

    //�X�V
    void Update();

    //�J��
    void Release();

    /// <summary>
    /// Imgui�̐���
    /// </summary>
    void InstantiateImgui();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

    /// <summary>
    /// �I�u�W�F�N�g�𐶐�����Imgui���o���֐�
    /// </summary>
    void ImguiIniObj();

    /// <summary>
    /// �V�[���`�F���W����Imgui�𐶐�����֐�
    /// </summary>
    void SceneChangeImgui();
    
    
};
