#include "PlayScene.h"
#include "Syari.h"
#include "Maguro.h"
#include "Stage.h"
#include "Controller.h"
#include "RedBox.h"
#include "BlueBox.h"
#include "Goal.h"
#include "Engine/Camera.h"
#include "Cannon.h"
#include "SalmonRoe.h"
#include "Engine/Image.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pos(0), hPict_(-1)
{
	//D3D11_BUFFER_DESC cb;
	//cb.ByteWidth = sizeof(ConstantBuffer);
	//cb.Usage = D3D11_USAGE_DYNAMIC;
	//cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cb.MiscFlags = 0;
	//cb.StructureByteStride = 0;

	//// �萔�o�b�t�@�̍쐬
	//Direct3D::pDevice_->CreateBuffer(&cb, NULL, &pConstantBuffer_);
}

//������
void PlayScene::Initialize()
{
	Instantiate<Syari>(this);
	Instantiate<Controller>(this);
	Instantiate<Stage>(this);
	Instantiate<RedBox>(this);
	Instantiate<BlueBox>(this);

	////�摜�f�[�^�̃��[�h
	//hPict_ = Image::Load("sky.png");
	//assert(hPict_ >= 0);
}

//�X�V
void PlayScene::Update()
{
	pos += UVSCROLL_SPEED;
}

//�`��
void PlayScene::Draw()
{
	//Direct3D::pContext_->VSSetConstantBuffers(1, 1, pConstantBuffer_.GetAddressOf());
	//Direct3D::pContext_->PSSetConstantBuffers(1, 1, pConstantBuffer_.GetAddressOf());

	//// �p�����[�^�̎󂯓n��
	//D3D11_MAPPED_SUBRESOURCE pdata;

	////��̍s��
	////uv���ړ��������
	//ConstantBuffer cb = { XMMatrixIdentity(),pos};

	//Direct3D::pContext_->Map(pConstantBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃��\�[�X�A�N�Z�X���ꎞ�~�߂�
	//memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		                    // ���\�[�X�֒l�𑗂�
	//Direct3D::pContext_->Unmap(pConstantBuffer_.Get(), 0);									    // GPU����̃��\�[�X�A�N�Z�X���ĊJ

	////�`��
	//Image::SetTransform(hPict_, transform_);
	//Image::Draw(hPict_, Direct3D::SHADER_UVSCROLL);
}

//�J��
void PlayScene::Release()
{
}
