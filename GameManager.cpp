#include "GameManager.h"
#include "Pause.h"
#include "Engine/Input.h"

namespace
{
	//pause�̃|�C���^
	Pause* pPause;

	//���Ԃ���~���Ă��邩
	bool isTimeMoving;
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
	}

	//�X�V
	void Update()
	{
		//�|�[�Y�L�[����������
		if (Input::IsKeyDown(DIK_1))
		{
			//�|�[�Y�̍X�V
			pPause->Update();

			//�Q�[�������Ԃ������Ă������~���A�~�܂��Ă����瓮����
			TimeMovingReverse();
		}
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
	void SetPausePos(XMFLOAT3 pos)
	{
		pPause->SetPos(pos);
	}
}