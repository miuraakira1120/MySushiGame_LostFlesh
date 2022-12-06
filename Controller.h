#pragma once
#include "Engine/GameObject.h"

class Controller : public GameObject
{
    const float CAMERA_SPEED = 1.5;
public:
    //�R���X�g���N�^
    Controller(GameObject* parent);

    //�f�X�g���N�^
    ~Controller();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���݈ʒu�̃Q�b�^�[
    XMFLOAT3 GetPosition();
};

