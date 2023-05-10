#pragma once
#include "Engine/GameObject.h"


//スタートシーンを管理するクラス
class StartScene : public GameObject
{
	//使用するiniファイルの名前
	const std::string iniFileName = "UI";

	int hPict_;    //画像番号
	int iniListButton;//タイトルシーンのボタンの番号
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StartScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
