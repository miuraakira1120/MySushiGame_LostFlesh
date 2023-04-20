#include "Pause.h"
#include "Engine/Input.h"

namespace 
{
	bool isPause;
}

void Pause::Initialize()
{
	isPause = false;
}

bool Pause::GetPause()
{
	return isPause;
}

void Pause::SetPause(bool pause)
{
	isPause = pause;
}

void Pause::ReversalPause()
{
	//isPauseを反転させる
	isPause = !isPause;
}

void Pause::Update()
{
	//1キーを押したら
	if (Input::IsKeyDown(DIK_1))
	{
		ReversalPause();
	}
}

