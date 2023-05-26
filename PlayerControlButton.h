#pragma once
#include <string>
#include "Button.h"

class PlayerControlButton : public Button
{
private:
	const XMFLOAT3 IMAGE_SIZE_DEF = { 1.0f, 1.0f, 1.0f };
	const XMFLOAT3 IMAGE_SIZE_MAG = { 1.1f, 1.1f, 1.0f };
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	PlayerControlButton(GameObject* parent, std::string fileName);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// ボタンが押された時の処理
	/// </summary>
	void Event() override;

	/// <summary>
	/// Update関数の前に呼ばれる関数
	/// </summary>
	void PreUpdate() override;
};

