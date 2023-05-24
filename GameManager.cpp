#include "GameManager.h"
#include "Pause.h"
#include "Engine/Input.h"

namespace
{
	//pauseのポインタ
	Pause* pPause;

	//時間が停止しているか
	bool isTimeMoving;

	//ポーズしているか
	bool isPause;
}

namespace GameManager
{
	//初期化
	void Initialize()
	{
		//各変数の初期化
		isTimeMoving = true;

		//ポーズ生成
		pPause = new Pause;
		pPause->Initialize();

		isPause = false;
	}

	//更新
	void Update()
	{
		//ポーズキーを押したら
		if (Input::IsKeyDown(DIK_1))
		{
			//UIの作成
			pPause->CreateUI();

			//ゲーム内時間が動いていたら停止し、止まっていたら動かす
			TimeMovingReverse();
		}
		//ポーズの更新
		pPause->Update();
	}

	//描画
	void Draw()
	{
		//時間が止まっていたら
		//if (!GetIsTimeMoving())
		{
			//ポーズ画面を描画
			pPause->Draw();
		}	
	}


	//解放
	void Release()
	{
		//解放処理
		if ((pPause) != nullptr)
		{
			delete (pPause);
			(pPause) = nullptr;
		}
	}

	//時間が動いているか
	bool GetIsTimeMoving()
	{
		return isTimeMoving;
	}

	//時間を動かすかどうか
	void SetTimeMoving(bool flag)
	{
		isTimeMoving = flag;
	}

	//時間が動いていたら停止し、止まっていたら動かす
	void TimeMovingReverse()
	{
		isTimeMoving = !isTimeMoving;
	}

	//isPauseのゲッター
	bool GetIsPause()
	{
		return false;
	}
}