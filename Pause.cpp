#include "Pause.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

namespace 
{
	int hPict_;    //画像番号
	bool isPause;  //ポーズされているか
	SceneManager* pSceneManager; //SceneManagerのポインタ
}

void Pause::Initialize()
{
	isPause = false;
	int hPict_ = -1;    //画像番号
}

void Pause::Initialize(SceneManager* pSceneManager_)
{
	isPause = false;
	pSceneManager = pSceneManager_;
	int hPict_ = -1;    //画像番号

	//画像データのロード
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

void Pause::Draw()
{
	if (isPause)
	{
		//Transform transform_ = pSceneManager->GetNowScenePointer()->GetTransform();
		//Image::SetTransform(hPict_, transform_);
		Image::Draw(hPict_);
	}
}

