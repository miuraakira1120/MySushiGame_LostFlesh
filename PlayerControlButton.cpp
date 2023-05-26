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

	//外枠を囲うようなシェーダー作る
	SetImage(ImageFullName, Direct3D::SHADER_2D);

}

void PlayerControlButton::Event()
{
	//プレイヤーのボタン操作を変えるUIや機能を出す
}

void PlayerControlButton::PreUpdate()
{
	//選ばれていたら画像を拡大する
	if (GetValue())
	{
		transform_.scale_ = IMAGE_SIZE_MAG;
	}
	else
	{
		transform_.scale_ = IMAGE_SIZE_DEF;
	}
}
