#pragma once
#include <DirectXMath.h>

using namespace DirectX;

enum TransMode
{
	TRANS_NORMAL_MODE,			//��{�I�ȍ��W
	TRANS_AXIS_MODE,			//�����ړ����ĉ�]���邩
	TRANS_CHANGEPARENT_MODE,	//�e��ς��Ĉړ�
	TRANS_MAX,
};

//-----------------------------------------------------------
//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
//-----------------------------------------------------------
class Transform
{
private:
	unsigned int axis_;			//�����ړ����ĉ�]���邩
	
public:
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;		//�g��s��
	XMFLOAT3 position_;		//�ʒu
	XMFLOAT3 rotate_;		//����
	XMFLOAT3 scale_;		//�g�嗦
	Transform * pParent_;	//�e�I�u�W�F�N�g�̏��
	XMFLOAT3 axisMatrix_;	//���̃}�g���N�X�����ɉ�]����
	
	

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	//�����F�Ȃ�
	//�ߒl�F�Ȃ�
	void Calclation();

	//���[���h�s����擾
	//�����F�Ȃ�
	//�ߒl�F���̎��_�ł̃��[���h�s��
	XMMATRIX GetWorldMatrix();

	/// <summary>
	/// XMFloat3�̑����Z
	/// </summary>
	/// <param name="����1 : ������鐔"></param>
	/// <param name="����2 : ������"></param>
	/// <returns></returns>
	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	/// <summary>
	/// XMFloat3�̈����Z
	/// </summary>
	/// <param name="����1 : ������鐔"></param>
	/// <param name="����2 : ������"></param>
	/// <returns></returns>
	static XMFLOAT3 Float3Sub(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/// <summary>
	/// XMFloat3�̕����̔��]
	/// </summary>
	/// <param name="����1 : ���]���鐔"></param>
	/// <returns></returns>
	static XMFLOAT3 Float3Reverse(XMFLOAT3 a)
	{
		return XMFLOAT3(-(a.x), -(a.y), -(a.z));
	}


	void MoveAxisRotate();  //�����ړ����ĉ�]����
	void NomalAxisRotate();	//�����ړ����Ȃ��ŉ�]����

	void SetAxisTrans(XMFLOAT3 mat);//���̎��ŉ��
};

