#include "PlayerControlButton.h"
#include "Engine/Direct3D.h"

PlayerControlButton::PlayerControlButton(GameObject* parent, std::string fileName)
	:Button(parent, "PlayerControlButton")
{
	pathName_ = fileName;
}

void PlayerControlButton::Initialize()
{
	std::string ImageFullName = ".\\Button/" + pathName_;

	//�O�g���͂��悤�ȃV�F�[�_�[���
	SetImage(ImageFullName, Direct3D::SHADER_2D);

}

void PlayerControlButton::Event()
{
	//�v���C���[�̃{�^�������ς���UI��@�\���o��
}

void PlayerControlButton::PreUpdate()
{
	//�I�΂�Ă�����摜���g�傷��
	if (GetValue())
	{
		transform_.scale_ = IMAGE_SIZE_MAG;
	}
	else
	{
		transform_.scale_ = IMAGE_SIZE_DEF;
	}
}
