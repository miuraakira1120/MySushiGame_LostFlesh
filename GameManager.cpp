#include "GameManager.h"
#include "Pause.h"
#include "Engine/Input.h"

namespace
{
	//pause�̃|�C���^
	Pause* pPause;

	//���Ԃ���~���Ă��邩
	bool isTimeMoving;

	//�|�[�Y���Ă��邩
	bool isPause;
}

namespace GameManager
{
	//������
	void Initialize()
	{
		//�e�ϐ��̏�����
		isTimeMoving = true;

		//�|�[�Y����
		pPause = new Pause;
		pPause->Initialize();

		isPause = false;
	}

	//�X�V
	void Update()
	{
		//�|�[�Y�L�[����������
		if (Input::IsKeyDown(DIK_1))
		{
			//UI�̍쐬
			pPause->CreateUI();

			//�Q�[�������Ԃ������Ă������~���A�~�܂��Ă����瓮����
			TimeMovingReverse();
		}
		//�|�[�Y�̍X�V
		pPause->Update();
	}

	//�`��
	void Draw()
	{
		//���Ԃ��~�܂��Ă�����
		//if (!GetIsTimeMoving())
		{
			//�|�[�Y��ʂ�`��
			pPause->Draw();
		}	
	}


	//���
	void Release()
	{
		//�������
		if ((pPause) != nullptr)
		{
			delete (pPause);
			(pPause) = nullptr;
		}
	}

	//���Ԃ������Ă��邩
	bool GetIsTimeMoving()
	{
		return isTimeMoving;
	}

	//���Ԃ𓮂������ǂ���
	void SetTimeMoving(bool flag)
	{
		isTimeMoving = flag;
	}

	//���Ԃ������Ă������~���A�~�܂��Ă����瓮����
	void TimeMovingReverse()
	{
		isTimeMoving = !isTimeMoving;
	}

	//isPause�̃Q�b�^�[
	bool GetIsPause()
	{
		return false;
	}
}