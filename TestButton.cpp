#include "TestButton.h"

//�R���X�g���N�^
TestButton::TestButton(GameObject* parent)
	:Button(parent, "TestButton")
{

}

//������
void TestButton::Initialize()
{
	SetImage("testButton.png");
}

void TestButton::Event()
{
	int a = 0;
}
