#pragma once

class SceneManager;

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
    /// �I�u�W�F�N�g��T���ē����֐�
    /// </summary>
    void FindAllObject();

    /// <summary>
    /// Imgui�̐���
    /// </summary>
    void InstantiateImgui();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
};
