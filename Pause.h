#pragma once
#include "Engine/GameObject.h"
#include <directxmath.h>

class Transform;

//Pause�V�[�����Ǘ�����N���X
class Pause
{
private:

public:
    //�R���X�g���N�^
    Pause();

    //�f�X�g���N�^
    ~Pause();

    //������
    void Initialize();

    //�X�V
    void Update();

    //�`��
    void Draw();

    //�J��
    void Release();

};