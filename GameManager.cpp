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

	//SceneManagerのポインタ
	SceneManager* pSceneManager;
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
			//ポーズ状態を逆にする関数
			PauseReverse();

			//ポーズしてたら
			if (isPause)
			{
				//UIの作成
				pPause->CreateUI();			
			}
			else
			{
				//UIの削除
				pPause->DeleteUI();
			}
		}
		//ポーズの更新
		pPause->Update();
	}

	//描画
	void Draw()
	{
		//ポーズしていたら
		if (isPause)
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
		return isPause;
	}
	void SetScenemanagerPointor(SceneManager* pScene)
	{
		pSceneManager = pScene;
	}
	SceneManager* GetpSceneManagerPointor()
	{
		return pSceneManager;
	}

	//ポーズ状態を逆にする関数
	void PauseReverse()
	{
		//isPauseを逆にする
		isPause = !isPause;

		//ゲーム内時間が動いていたら停止し、止まっていたら動かす
		TimeMovingReverse();
	}
}