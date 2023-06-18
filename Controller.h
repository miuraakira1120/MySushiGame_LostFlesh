#pragma once
#include "Engine/GameObject.h"

class Controller : public GameObject
{
    const float CAMERA_SPEED = 3.0f;
    const float UP_ANGLE_LIMIT = 1000;
    const float DOWN_ANGLE_LIMIT = -1000;
    const float PAD_SPEED = 3.0f;
    int hPict_;    //�摜�ԍ�

    XMFLOAT3 cameraDistance;//�R���g���[���[����J�����̋���

    const float MOVED_FOV = XM_PIDIV4 * 1.1f; // �v���C���[���ړ����Ă��鎞��FoV
    const float FOV = XM_PIDIV4; // �v���C���[�������~�܂��Ă��鎞��FoV
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
    /// �R���g���[���[�ŃJ��������]������֐�
    /// </summary>
    /// <param name="position">�R���g���[���[�̈ʒu��ς���</param>
    void SetCameraPos(XMFLOAT3 position);

    /// <summary>
    /// ���[�v���g�p���ăR���g���[���[�ŃJ��������]������֐�
    /// </summary>
    /// <param name="position">���B����ׂ��ʒu</param>
    /// <param name="attenRate">�����䗦(1{���{ }���0.1�̕�����������)</param>
    void SetCameraLerpPos(XMFLOAT3 position, float attenRate);

    /// <summary>
    /// ���[�v����FoV�g�p���ăR���g���[���[�ŃJ��������]������֐�
    /// �����Ă������ǂ����ɂ����FoV��ύX
    /// </summary>
    /// <param name="isMoved">�����Ă�����</param>
    void ChangeFovMove(bool isMoved);
};

