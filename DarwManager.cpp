#include "DarwManager.h"

//�R���X�g���N�^
DrawManager::DrawManager(GameObject* parent)
    :GameObject(parent, "DrawManager"), screenSeparation(1)
{
}

//�f�X�g���N�^
DrawManager::~DrawManager()
{
}

//������
void DrawManager::Initialize()
{
}

//�X�V
void DrawManager::Update()
{
}

//�`��
void DrawManager::Draw()
{
}

//�J��
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
