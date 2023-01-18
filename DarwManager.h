#pragma once
#include "Engine/GameObject.h"

//�`����Ǘ�����N���X
class DrawManager : public GameObject
{
    //��ʕ�����
    int screenSeparation;
public:
    //�R���X�g���N�^
    DrawManager(GameObject* parent);

    //�f�X�g���N�^
    ~DrawManager();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�Q�b�^�[
    int GetScreenSeparation();

    //�Z�b�^�[
    void SetScreenSeparation(int num);
};