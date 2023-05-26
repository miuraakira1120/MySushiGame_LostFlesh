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
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	PlayerControlButton(GameObject* parent, std::string fileName);

	/// <summary>
	/// ������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �{�^���������ꂽ���̏���
	/// </summary>
	void Event() override;

	/// <summary>
	/// Update�֐��̑O�ɌĂ΂��֐�
	/// </summary>
	void PreUpdate() override;
};

