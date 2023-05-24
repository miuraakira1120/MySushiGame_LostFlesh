#pragma once

class Pause;

namespace GameManager
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//解放
	void Release();

	/// <summary>
	/// 時間が動いているか
	/// </summary>
	/// <returns></returns>
	bool GetIsTimeMoving();
	
	/// <summary>
	/// 時間を動かすかどうか
	/// </summary>
	/// <param name="flag"></param>
	void SetTimeMoving(bool flag);

	/// <summary>
	/// 時間が動いていたら停止し、止まっていたら動かす
	/// </summary>
	void TimeMovingReverse();

	/// <summary>
	/// isPauseのゲッター
	/// </summary>
	/// <returns></returns>
	bool GetIsPause();
};

