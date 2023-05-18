#pragma once
#include "Engine/GameObject.h"


//�X�^�[�g�V�[�����Ǘ�����N���X
class StartScene : public GameObject
{
	//�g�p����ini�t�@�C���̖��O
	const std::string iniFileName = "UI.ini";

	// �g�p����JSON�t�@�C���̖��O
	const std::string TITLE_JSON = "../Assets\\GameData\\TitleScene.json";

	int hPict_;    //�摜�ԍ�
	int iniListButton;//�^�C�g���V�[���̃{�^���̔ԍ�

	GameObject* pStartButton;
	
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StartScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
