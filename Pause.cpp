#include "Pause.h"
#include "Engine/Image.h"

//�R���X�g���N�^
Pause::Pause()
{
}

//�f�X�g���N�^
Pause::~Pause()
{
}

//������
void Pause::Initialize()
{
}

//�X�V
void Pause::Update()
{
    //�쐬����UI�̍X�V���Ă�
    pCreateUI_->AllCreateStageUpdate();
}

//�`��
void Pause::Draw()
{
	//�����`�悵�Ă��Ȃ��̂Ȃ�
	if (!isDrawUI_) return;

	//�쐬����UI�̕`����Ă�
	pCreateUI_->AllCreateStageDraw();
}

//�J��
void Pause::Release()
{
}

