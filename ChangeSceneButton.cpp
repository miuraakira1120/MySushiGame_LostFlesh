#include "ChangeSceneButton.h"

ChangeSceneButton::ChangeSceneButton(GameObject* parent, SCENE_ID name, std::string fileName)
	:Button(parent, "ChangeSceneButton"), changeSceneName(name), ImageName(fileName)
{
}

void ChangeSceneButton::Initialize()
{
	std::string ImageFullName = ".\\Button/" + ImageName;
	SetImage(ImageFullName);
}

void ChangeSceneButton::Event()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(changeSceneName);
}

void ChangeSceneButton::SetChangeSceneName(SCENE_ID name)
{
	changeSceneName = name;
}

void ChangeSceneButton::PreUpdate()
{
	
	if (GetValue())
	{
		transform_.scale_ = IMAGE_SIZE_MAG;
	}
	else
	{
		transform_.scale_ = IMAGE_SIZE_DEF;
	}
}
