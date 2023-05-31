#include "ImageBase.h"
#include "Engine/Image.h"

//�R���X�g���N�^
ImageBase::ImageBase(GameObject* parent, std::string pathName, int alpha)
    :GameObject(parent, "ImageBase"),hPict_(-1)
{
    SetPathName(pathName);
    SetAlpha(alpha);
}

//�f�X�g���N�^
ImageBase::~ImageBase()
{
}

//������
void ImageBase::Initialize()
{
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load(pathName_);
    assert(hPict_ >= 0);
}

//�X�V
void ImageBase::Update()
{
}

//�`��
void ImageBase::Draw()
{
    Image::SetAlpha(hPict_, alpha_);
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

//�J��
void ImageBase::Release()
{
}