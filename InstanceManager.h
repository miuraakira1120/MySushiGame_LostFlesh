#pragma once
#include <string>
#include <DirectXMath.h>

using namespace DirectX;

class GameObject;

//JSON��p���ăI�u�W�F�N�g���쐬����
namespace InstanceManager
{
	//JSON�̏��ŃI�u�W�F�N�g���쐬���邽�߂̍\����
	struct InstantiateInfoJSON
	{
		GameObject* parent;				//�e�N���X
		std::string loadFile;			//�ǂݍ��މ摜
		XMFLOAT3 position;		//�ʒu
		XMFLOAT3 rotate;		//����
		XMFLOAT3 scale;		//�g�嗦
		GameObject* object;				//�ǂ�ȃI�u�W�F�N�g�𐶐����邩
	};


	/// <summary>
	/// �I�u�W�F�N�g�𐶐����邽�߂̏���JSON����ǂݍ���
	/// </summary>
	/// <param name="filename">�Z�N�V����</param>
	/// <param name="key">�L�[</param>
	/// <param name="info">�l������\����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetInstanceInfo(std::string filename, std::string key, InstantiateInfoJSON& info);

	//JSONOpe�ɒl�S�����֐����������@InstantiateInfoJSON�̒��ɓ����@�Ă���

	//InstantiateInfoJSON��p���ăI�u�W�F�N�g���쐬����

	//�C���X�^���X�I�u�W�F�N�g�݂����Ȃ̂Ŋ����ł���悤��
};

