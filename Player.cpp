#include "Player.h"
#include "Engine/Camera.h"
#include "Controller.h"


Player::Player(GameObject* parent, std::string pathName)
	:PlayerBase(parent, "Player", pathName)
{

}

//������
void Player::Initialize()
{
}

//�X�V
void Player::Update()
{
	//�J�����̃R���g���[���[��T��
	Controller* pController = (Controller*)FindObject("Controller");
	Camera::SetTarget(transform_.position_);
	Camera::SetPosition(pController->GetCameraPos());
}

//���
void Player::Release()
{
}
