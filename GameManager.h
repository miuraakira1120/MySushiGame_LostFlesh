#pragma once

class Pause;

namespace GameManager
{
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
};

