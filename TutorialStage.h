#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class TutorialStage : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    TutorialStage(GameObject* parent);

    //�f�X�g���N�^
    ~TutorialStage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�n���h�����擾����֐�
    int GetModelHandle() { return hModel_; }
};
