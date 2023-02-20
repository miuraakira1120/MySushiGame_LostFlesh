#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Ball : public GameObject
{
    int hModel_;    //���f���ԍ�
    XMFLOAT3 fMove;
public:
    //�R���X�g���N�^
    Ball(GameObject* parent);

    //�f�X�g���N�^
    ~Ball();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�Z�b�^�[
    void SetMove(XMFLOAT3 move);
    void SetPosition(XMFLOAT3 pos);
};