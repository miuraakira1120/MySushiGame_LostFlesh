#pragma once
namespace Pause
{
	//初期化
	void Initialize();

	//isPauseのゲッター
	bool GetPause();

	//isPauseのセッター
	void SetPause(bool pause);

	//isPauseを反転させる
	void ReversalPause();

	//更新
	void Update();
};

