#include "RootObject.h"
#include "SceneManager.h"
#include "../Imgui_Obj.h"


RootObject::RootObject():
	GameObject(nullptr, "RootObject")
{
}


RootObject::~RootObject()
{
}

void RootObject::Initialize()
{
	Instantiate<SceneManager>(this);

#if _DEBUG
	Instantiate<Imgui_Obj>(this);
#endif // DEBUG_
}

void RootObject::Update()
{
}

void RootObject::Draw()
{
}

void RootObject::Release()
{
}
