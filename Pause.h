#pragma once

class SceneManager;

namespace Pause
{

	// 初期化
	void Initialize();

	//初期化
	void Initialize(SceneManager* pSceneManager);
	

	//isPauseのゲッター
	bool GetPause();

	//isPauseのセッター
	void SetPause(bool pause);

	//isPauseを反転させる
	void ReversalPause();

	//更新
	void Update();

	//描画
	void Draw();
};

