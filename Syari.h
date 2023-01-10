#pragma once
#include "Engine/GameObject.h"
#include <vector>

#define VERTEX_VLU 8

const float SYARI_SIZE_X = 0.5f; //�V������X�̃T�C�Y�i1�{�j
const float SYARI_SIZE_Y = 0.5f; //�V������Y�̃T�C�Y�i1�{�j
const float SYARI_SIZE_Z = 1.0f; //�V������Z�̃T�C�Y�i1�{�j

using std::vector;



class Syari : public GameObject
{

    enum Ver
    {
        UP_RIGHT_FRONT = 0,
        UP_RIGHT_BACK,
        UP_LEFT_FRONT,
        UP_LEFT_BACK,
        DOWN_RIGHT_FRONT,
        DOWN_RIGHT_BACK,
        DOWN_LEFT_FRONT,
        DOWN_LEFT_BACK,

    };
    
   
    const float ROTATE_SPEED = 0.5f; //�V�����̉�]�̃X�s�[�h
    const float FALL_SPEED   = 0.1f; //������X�s�[�h

    const XMVECTOR upRightFrontPos =   { 0.5f, 0.5f, 1.0f    };//�V�����̏�E�O�̈ʒu
    const XMVECTOR upRightBackPos =    { 0.5f, 0.5f, -1.0f   };//�V�����̏�E��̈ʒu
    const XMVECTOR upLeftFrontPos =    { -0.5f, 0.5f, 1.0f   };//�V�����̏㍶�O�̈ʒu
    const XMVECTOR upLeftBackPos =     { -0.5f, 0.5f, -1.0f  };//�V�����̏㍶��̈ʒu
    const XMVECTOR downRightFrontPos = { 0.5f, -0.5f, 1.0f   };//�V�����̉����O�̈ʒu
    const XMVECTOR downRightBackPos =  { 0.5f, -0.5f, -1.0f  };//�V�����̉��E��̈ʒu
    const XMVECTOR downLeftFrontPos =  { -0.5f, -0.5f, 1.0f  };//�V�����̉����O�̈ʒu
    const XMVECTOR downLeftBackPos =   { -0.5f, -0.5f, -1.0f };//�V�����̉�����̈ʒu

    vector<XMVECTOR> vVertexPos;
    int hModel_;    //���f���ԍ�
    int mode;     //���[�h
    bool breakFlag = false;

   

public:
   
    //�R���X�g���N�^
    Syari(GameObject* parent);

    //�f�X�g���N�^
    ~Syari();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //position�̃Q�b�^�[
    XMFLOAT3 GetPosition();

    //rotate�̃Q�b�^�[
    XMFLOAT3 GetRotate();

    int GetModelHandle() { return hModel_; }

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;
};