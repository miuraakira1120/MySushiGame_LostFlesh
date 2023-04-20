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
	//isPause�𔽓]������
	isPause = !isPause;
}

void Pause::Update()
{
	//1�L�[����������
	if (Input::IsKeyDown(DIK_1))
	{
		ReversalPause();
	}
}

