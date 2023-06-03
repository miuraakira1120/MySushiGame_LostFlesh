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
    std::string fullPath = Image::DIRECTORY_UI + pathName_;
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load(fullPath);
    assert(hPict_ >= 0);

    PrevPathName_ = pathName_;
}

//�X�V
void ImageBase::Update()
{
    //�O�t���[����pathName_���Ⴄ�Ȃ�
    if (PrevPathName_ != pathName_)
    {
        std::string fullPath = Image::DIRECTORY_UI + pathName_;
        //�����[�h
        //�摜�f�[�^�̃��[�h
        hPict_ = Image::Load(fullPath);
        assert(hPict_ >= 0);
    }
    PrevPathName_ = pathName_;
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