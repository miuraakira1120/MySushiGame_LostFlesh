#include "Pause.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

namespace 
{
	int hPict_;    //�摜�ԍ�
	bool isPause;  //�|�[�Y����Ă��邩
	SceneManager* pSceneManager; //SceneManager�̃|�C���^
}

void Pause::Initialize()
{
	isPause = false;
	int hPict_ = -1;    //�摜�ԍ�
}

void Pause::Initialize(SceneManager* pSceneManager_)
{
	isPause = false;
	pSceneManager = pSceneManager_;
	int hPict_ = -1;    //�摜�ԍ�

	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("BlackBack.jpg");
	assert(hPict_ >= 0);
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

void Pause::Draw()
{
	if (isPause)
	{
		//Transform transform_ = pSceneManager->GetNowScenePointer()->GetTransform();
		//Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

