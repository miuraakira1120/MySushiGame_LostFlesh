#include "DarwManager.h"

//コンストラクタ
DrawManager::DrawManager(GameObject* parent)
    :GameObject(parent, "DrawManager"), screenSeparation(1)
{
}

//デストラクタ
DrawManager::~DrawManager()
{
}

//初期化
void DrawManager::Initialize()
{
}

//更新
void DrawManager::Update()
{
}

//描画
void DrawManager::Draw()
{
}

//開放
void DrawManager::Release()
{
}

int DrawManager::GetScreenSeparation()
{
    return screenSeparation;
}

void DrawManager::SetScreenSeparation(int num)
{
    screenSeparation = num;
}
