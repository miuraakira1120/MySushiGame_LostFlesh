#pragma once
#include "Engine/GameObject.h"

class Controller : public GameObject
{
    const float CAMERA_SPEED = 3.0f;
    const float UP_ANGLE_LIMIT = 1000;
    const float DOWN_ANGLE_LIMIT = -1000;
    const float PAD_SPEED = 3.0f;
    int hPict_;    //�摜�ԍ�
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

    /// <summary>
    /// �J�����̈ʒu�̃Q�b�^�[
    /// </summary>
    /// <param name="position">���̃I�u�W�F�N�g���Ή����Ă���I�u�W�F�N�g�̈ʒu</param>
    /// <returns></returns>
    XMFLOAT3 GetCameraPos(XMFLOAT3 position);
};

