#pragma once
#include "Engine/GameObject.h"

class Maguro : public GameObject
{
    const float MAGURO_SIZE_X = 0.25f; //�}�O����X�̃T�C�Y�i1�{�j
    const float MAGURO_SIZE_Y = 0.25f; //�}�O����Y�̃T�C�Y�i1�{�j
    const float MAGURO_SIZE_Z = 1.5f;  //�}�O����Z�̃T�C�Y�i1�{�j

    const float FALL_ANGLE = 5.0f;    //������p�x
    const short ROTATE_MAX = 360;      //��]�̍ő�
    const float FALL_SPEED = 0.2f * 0.01f;     //������X�s�[�h

    int hModel_;    //���f���ԍ�
    bool fallFlag;  //�}�O���������邩�ǂ����t���O

    XMFLOAT3 pravPos;//1f�O�̎����̈ʒu
    
public:
    //�R���X�g���N�^
    Maguro(GameObject* parent);

    //�f�X�g���N�^
    ~Maguro();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�e�̐e���猩���ʒu�����
    XMFLOAT3 GetParentPos()
    {
        return Transform::Float3Add(GetParent()->GetPosition(), transform_.position_);
    }

   
};