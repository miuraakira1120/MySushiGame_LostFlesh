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

    /// <summary>
    /// imgui�Ń{�^���𐶐�������ɂ�邱��
    /// </summary>
    void RearButtonInstantiate();
    
    //������{�^���̍Ĉړ������o����悤�ɂ���
    void ReSettingButton();

    /// <summary>
    /// �{�^���쐬���[�h�̎��ɏo��imgui
    /// </summary>
    void CreateButtonImgui();

    /// <summary>
    /// �摜�쐬���[�h�̎��ɏo��Imgui(Begin�̒��Ŏg��)
    /// </summary>
    void CreateImageImgui();

    /// <summary>
    /// �I�u�W�F�N�g�𐶐����鎞�Ɋ�{�I��Imgui���o��(Begin�̒��Ŏg��)
    /// </summary>
    void SettingBasicImgui();

    /// <summary>
    /// �g���q��ǉ�����֐�(�ϐ�extension���Q��)
    /// </summary>
    /// <returns>�Ԃ��g���q</returns>
    std::string AddExtension();

};
