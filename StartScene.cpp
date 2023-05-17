#include "StartScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "ButtonManager.h"
#include "Engine/IniOperator.h"
#include "Imgui_Obj.h"
#include "Pause.h"
#include "JsonOperator.h"

//�R���X�g���N�^
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), hPict_(-1)
{
}

//������
void StartScene::Initialize()
{
	////�摜�f�[�^�̃��[�h
	//hPict_ = Image::Load("start.jpg");
	//assert(hPict_ >= 0);

	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	pStartButton = ButtonManager::CreateSceneChangeButton(this, pos, SCENE_ID_PLAY, "GameStartButton.png");

	int iniListButton = IniOperator::AddList(iniFileName, "TitleButton");
	pStartButton->SetPosition(IniOperator::GetValue(iniListButton, "ChangeSceneButtonX",0), IniOperator::GetValue(iniListButton, "ChangeSceneButtonY",0), 0);

	/*string str = "yo";
	if (JsonOperator::GetJSONString("test.json", "key", str))
	{
		int i = 0;
	}
	int a = 0;*/

	/*float i = 0;
	if (JsonOperator::GetJSONFloat("test.json","Button", "posX", i))
	{
		int j = 0;
	}
	int ij= 0;
	if (JsonOperator::GetJSONFloat("test.json", "Button", "posY", i))
	{
		int j = 0;
	}*/

	

	// JSON���t�@�C���ɏ�������
	std::string filename = "../Assets\\GameData\\output.json";
	if (JsonOperator::WriteJSONToFile(filename, "a", "a", (float)30.0))
	{
		int success = 1;
	}
	else
	{
		int success = 0;
	}
}

//�X�V
void StartScene::Update()
{
	//SetCurrentDirectory("Assrets");
	//int isPlaySe_ = GetPrivateProfileInt("Option", "Key", 1, ".\\/Config/test.ini");
	////filesystem
	//int a = 7;

#if _DEBUG
	pStartButton->SetPosition(IniOperator::GetValue(iniListButton, "ChangeSceneButtonX"), IniOperator::GetValue(iniListButton, "ChangeSceneButtonY"), 0);
#endif
	
}

//�`��
void StartScene::Draw()
{
	/*Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);*/
}

//�J��
void StartScene::Release()
{
}