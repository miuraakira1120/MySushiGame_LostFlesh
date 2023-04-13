#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"

//選ばれていない
void Button::UnSelect()
{
	select_ = false;
}

//選ばれている
void Button::Select()
{
	select_ = true;
}

//押された時の処理
void Button::Event()
{
}

//コンストラクタ
Button::Button(GameObject* parent, const std::string& name)
{
}

//更新
void Button::Update()
{
    //マウス操作
    if (operationRight_)
    {
        //画面のサイズ
        const XMVECTOR windowSize = XMVectorSet(static_cast<float>(Direct3D::screenWidth_), static_cast<float>(Direct3D::screenHeight_), 0.0f, 0.0f);

        value_ = 0.0f;

        //ボタン上にあるか
        if (Image::OnMouseOver(hPict_))
        {
            value_ = 0.2f;
            move_ += 0.01f;
            Select();
        }
        else
        {
            move_ = 0.f;
        }

    }

    if (select_)
    {
        //押されたか
        if (Input::IsMouseButtonDown(0) || Input::IsMouseButton(1))
        {
            Event();
        }
    }

    UnSelect();
}

//描画
void Button::Draw()
{
    //描画
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

//解放
void Button::Release()
{
}

//画像の設定
void Button::SetImage(const std::string& path)
{
}

//マウスによるボタン操作の権限剥奪
void Button::NoRight()
{
}

//マウスによるボタン操作の権限付与
void Button::Right()
{
}
