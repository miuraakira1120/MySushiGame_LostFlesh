#include "Pause.h"
#include "Engine/Image.h"

//コンストラクタ
Pause::Pause()
{
}

//デストラクタ
Pause::~Pause()
{
}

//初期化
void Pause::Initialize()
{
}

//更新
void Pause::Update()
{
    //作成したUIの更新を呼ぶ
    pCreateUI_->AllCreateStageUpdate();
}

//描画
void Pause::Draw()
{
	//もし描画していないのなら
	if (!isDrawUI_) return;

	//作成したUIの描画を呼ぶ
	pCreateUI_->AllCreateStageDraw();
}

//開放
void Pause::Release()
{
}

