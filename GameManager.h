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
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//���
	void Release();

	/// <summary>
	/// ���Ԃ������Ă��邩
	/// </summary>
	/// <returns></returns>
	bool GetIsTimeMoving();
	
	/// <summary>
	/// ���Ԃ𓮂������ǂ���
	/// </summary>
	/// <param name="flag"></param>
	void SetTimeMoving(bool flag);

	/// <summary>
	/// ���Ԃ������Ă������~���A�~�܂��Ă����瓮����
	/// </summary>
	void TimeMovingReverse();

	/// <summary>
	/// isPause�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	bool GetIsPause();

	/// <summary>
	/// �V�[���}�l�[�W���[�̃|�C���^���Z�b�g����
	/// </summary>
	void SetScenemanagerPointor(SceneManager* pSceneManager);

	/// <summary>
	/// �V�[���}�l�[�W���[�̃|�C���^�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	SceneManager* GetpSceneManagerPointor();

	/// <summary>
	/// �|�[�Y��Ԃ��t�ɂ���֐�
	/// </summary>
	void PauseReverse();

	/// <summary>
	/// �|�[�Y��Ԃ�ݒ肷��֐�
	/// </summary>
	/// <param name="pause">�|�[�Y���邩�ǂ���</param>
	void SetPause(bool pause);

	/// <summary>
	/// pPause�̃Q�b�^�[
	/// </summary>
	/// <returns></returns>
	Pause* GetPauseClass();

};

