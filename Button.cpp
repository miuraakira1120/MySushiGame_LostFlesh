#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"

//�I�΂�Ă��Ȃ�
void Button::UnSelect()
{
	select_ = false;
}

//�I�΂�Ă���
void Button::Select()
{
	select_ = true;
}

//�����ꂽ���̏���
void Button::Event()
{
}

//�R���X�g���N�^
Button::Button(GameObject* parent, const std::string& name)
    :GameObject(parent, name), hPict_(-1), value_(0.0f), select_(false), operationRight_(true)
{
}

//�X�V
void Button::Update()
{
    //�}�E�X����
    if (operationRight_)
    {
        //��ʂ̃T�C�Y
        const XMVECTOR windowSize = XMVectorSet(static_cast<float>(Direct3D::screenWidth_), static_cast<float>(Direct3D::screenHeight_), 0.0f, 0.0f);

        value_ = 0.0f;

        //�{�^����ɂ��邩
        if (Image::OnMouseOver(hPict_))
        {
            value_ = 0x01;
            Select();
        }
    }

    if (select_)
    {
        //�����ꂽ��
        if (Input::IsMouseButtonDown(0) || Input::IsMouseButton(1))
        {
            Event();
        }
    }

    UnSelect();
}

//�`��
void Button::Draw()
{

    //�`��
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_);
}

//���
void Button::Release()
{
}

//�摜�̐ݒ�
void Button::SetImage(const std::string& name)
{
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load(name);

    //���[�h���ꂽ���m�F
    assert(hPict_ >= 0);
}

//�}�E�X�ɂ��{�^������̌������D
void Button::NoRight()
{
    operationRight_ = false;
    UnSelect();
}

//�}�E�X�ɂ��{�^������̌����t�^
void Button::Right()
{
    operationRight_ = true;
    Select();
}
