#pragma once
#include "Engine/GameObject.h"
#include "Maguro.h"
#include "Syari.h"
#include "Engine/Text.h"

//imgui���Ǘ�����N���X
class Imgui_Obj : public GameObject
{
    Maguro* pMaguro;
    Syari* pSyari;
    Text* pText;

public:
    //�R���X�g���N�^
    Imgui_Obj(GameObject* parent);

    //�f�X�g���N�^
    ~Imgui_Obj();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    /// <summary>
    /// �I�u�W�F�N�g��T���ē����֐�
    /// </summary>
    void FindAllObject();

    /// <summary>
    /// Imgui�̐���
    /// </summary>
    void InstantiateImgui();
};
