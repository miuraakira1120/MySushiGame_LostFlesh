#pragma once
#include "Engine/GameObject.h"

class Controller : public GameObject
{
    const float CAMERA_SPEED = 1.5f;
    const float UP_ANGLE_LIMIT = 30;
    const float DOWN_ANGLE_LIMIT = -45;
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

    //�����̃Q�b�^�[
    XMFLOAT3 GetRotate();
    XMFLOAT3 GetCameraPos();
};

