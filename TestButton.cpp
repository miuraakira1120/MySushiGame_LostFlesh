#include "TestButton.h"

//コンストラクタ
TestButton::TestButton(GameObject* parent)
	:Button(parent, "TestButton")
{

}

//初期化
void TestButton::Initialize()
{
	SetImage("testButton.png");
}

void TestButton::Event()
{
	int a = 0;
}
