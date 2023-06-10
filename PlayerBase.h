#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Engine/GameObject.h"
#include "Engine/Direct3D.h"

class Controller;

using namespace DirectX;

class PlayerBase : public GameObject
{
private:
    //�萔
    const float FALL_SPEED_LIMIT = 0.5f;    //�����̑��x���E 
    const float SPEED_OF_JUMP = 0.4f;       //�������x
    const float FALL_SPEED = 0.02f;         //������X�s�[�h
    const float SYARI_SPEED = 0.25f;        //�V�����̃X�s�[�h

    //�v���C���[�̃T�C�Y
    const XMFLOAT3 PLAYER_SIZE{
        0.5f,        //�V������X�̃T�C�Y�i1�{�j
        0.5f,        //�V������Y�̃T�C�Y�i1�{�j
        1.0f,        //�V������Z�̃T�C�Y�i1�{�j
    };

    static const int   DIRECTION_ARRAY_SIZE = 3;   //�������i�[���ꂽ�z��̃T�C�Y

    int   hModel_;               //���f���ԍ�
    bool  isGround;              //�n�ʂɐݒu���Ă��邩
    float gravity;               //���󂯂Ă���d�̗͂�(�}�C�i�X�Ȃ�d�͂�U��؂��ď�ɍs��)
    bool  canMove;               //�������Ƃ��ł��邩
    XMFLOAT3 size;               //�v���C���[�̃T�C�Y
    Direct3D::SHADER_TYPE type;  //�`��Ɏg�p����V�F�[�_�[
    Controller* pController;

public:

    //�R���X�g���N�^
    PlayerBase(GameObject* parent, std::string name, std::string pathName);

    //������
    virtual void Initialize() {};

    //�X�V
    virtual void Update() {};

    //�`��
    virtual void Draw();

    //�J��
    virtual void Release() {};

    //�Z�b�g�A�b�v����֐�
    virtual void SetUp();

    //�����ɓ�������
   //�����FpTarget ������������
    virtual void OnCollision(GameObject* pTarget) {};

    //�W�����v����
    void Jump();

    /// <summary>
    /// �ړ�����֐�
    /// </summary>
    /// <param name="isInverse">�o�b�N���邩�ǂ���</param>
    void Move(bool isInverse = false);

    //���f���̃Q�b�^�[
    int GetModelHandle() { return hModel_; }

    //�d�͂̏���
    void Gravity();

    /// <summary>
    /// �Փ˂��Ă��邩���ׂ�
    /// </summary>
    /// <param name="hStageModel">�X�e�[�W�̃��f��</param>
    /// <param name="vec">���C���΂�����</param>
    /// <param name="rayPos">���C���ǂ������΂���</param>
    /// <param name="length">�߂�����</param>
    /// <returns>�Փ˂������ǂ���</returns>
    bool CheckIfCollided(int hStageModel, XMFLOAT3 vec,XMFLOAT3 rayPos, float &length);
    
    /// <summary>
    /// �p����n�ʂ̖@���ɓY�킹��
    /// </summary>
    /// <param name="hStageModel">�X�e�[�W�̃��f��</param>
    void PostureGroundFollow(int hStageModel);

    /// <summary>
    /// ���̃I�u�W�F�N�g�ɃJ�������Z�b�g����
    /// </summary>
    void SetCameraController(XMFLOAT3 ShiftPos = XMFLOAT3(0.0f,0.0f,0.0f));


    /// <summary>
    /// �n�ʂɂ߂荞�񂾎��̏���
    /// </summary>
    /// <param name="hStageModel">�X�e�[�W�̃��f��</param>
    void RevertProcess(int hStageModel);
};
