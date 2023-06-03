#include "ImageBase.h"
#include "Engine/Image.h"

//コンストラクタ
ImageBase::ImageBase(GameObject* parent, std::string pathName, int alpha)
    :GameObject(parent, "ImageBase"),hPict_(-1)
{
    SetPathName(pathName);
    SetAlpha(alpha);
}

//デストラクタ
ImageBase::~ImageBase()
{
}

//初期化
void ImageBase::Initialize()
{
    std::string fullPath = Image::DIRECTORY_UI + pathName_;
    //画像データのロード
    hPict_ = Image::Load(fullPath);
    assert(hPict_ >= 0);

    PrevPathName_ = pathName_;
}

//更新
void ImageBase::Update()
{
    //前フレームとpathName_が違うなら
    if (PrevPathName_ != pathName_)
    {
        std::string fullPath = Image::DIRECTORY_UI + pathName_;
        //リロード
        //画像データのロード
        hPict_ = Image::Load(fullPath);
        assert(hPict_ >= 0);
    }
    PrevPathName_ = pathName_;
}

//描画
void ImageBase::Draw()
{
    Image::SetAlpha(hPict_, alpha_);
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

//開放
void ImageBase::Release()
{
}