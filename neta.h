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
    virtual void Initialize() = 0;

    //�X�V
    virtual void Update() = 0;

    //�`��
    virtual void Draw() = 0;

    //�J��
    virtual void Release() = 0;
};