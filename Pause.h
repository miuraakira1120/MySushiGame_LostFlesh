#pragma once

class SceneManager;

namespace Pause
{

	// ������
	void Initialize();

	//������
	void Initialize(SceneManager* pSceneManager);
	

	//isPause�̃Q�b�^�[
	bool GetPause();

	//isPause�̃Z�b�^�[
	void SetPause(bool pause);

	//isPause�𔽓]������
	void ReversalPause();

	//�X�V
	void Update();

	//�`��
	void Draw();
};

