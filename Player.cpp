#include "Player.h"
#include "Engine/Camera.h"
#include "Controller.h"


Player::Player(GameObject* parent, std::string pathName)
	:PlayerBase(parent, "Player", pathName)
{

}

//初期化
void Player::Initialize()
{
}

//更新
void Player::Update()
{
	//カメラのコントローラーを探す
	Controller* pController = (Controller*)FindObject("Controller");
	Camera::SetTarget(transform_.position_);
	Camera::SetPosition(pController->GetCameraPos());
}

//解放
void Player::Release()
{
}
