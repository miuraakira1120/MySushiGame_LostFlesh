#pragma once
#include "Engine/GameObject.h"

//�摜���o�������̃N���X
class ImageBase : public GameObject
{
    int hPict_;                //�摜�ԍ�
    std::string PrevPathName_; //1�t���[���O�̉摜�ԍ�

public:
    //�R���X�g���N�^
    ImageBase(GameObject* parent, std::string pathName, int alpha = 255);

    //�f�X�g���N�^
    ~ImageBase();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};