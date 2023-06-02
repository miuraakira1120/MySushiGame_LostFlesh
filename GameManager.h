#pragma once


class Pause;
class SceneManager;

namespace GameManager
{
	enum class ParentNum
	{
		NOW_SCENE,
		PAUSE,
		PLAYER,
		PARENT_MAX
	};

	

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

	/// <summary>
	/// シーンマネージャーのポインタをセットする
	/// </summary>
	void SetScenemanagerPointor(SceneManager* pSceneManager);

	/// <summary>
	/// シーンマネージャーのポインタのゲッター
	/// </summary>
	/// <returns></returns>
	SceneManager* GetpSceneManagerPointor();

	/// <summary>
	/// ポーズ状態を逆にする関数
	/// </summary>
	void PauseReverse();

	/// <summary>
	/// ポーズ状態を設定する関数
	/// </summary>
	/// <param name="pause">ポーズするかどうか</param>
	void SetPause(bool pause);

	/// <summary>
	/// pPauseのゲッター
	/// </summary>
	/// <returns></returns>
	Pause* GetPauseClass();

};

