#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Stage : public GameObject
{
    int hModel_;    //���f���ԍ�
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

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
