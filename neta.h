#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Neta : public GameObject
{

public:
    //�R���X�g���N�^
    Neta(GameObject* parent);

    //�f�X�g���N�^
    ~Neta();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};