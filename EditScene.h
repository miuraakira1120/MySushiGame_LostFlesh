#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"

//UIなどを作るときに使用するシーンを管理するクラス
class EditScene : public GameObject
{
	UI_Type modeUI;				//どのUIをいじっているか
	UI_Type prevModeUI;			//1f前までどのUIをいじっていたか

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	EditScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
