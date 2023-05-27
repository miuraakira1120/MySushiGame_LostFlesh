#pragma once
#include <string>
#include <DirectXMath.h>

using namespace DirectX;

class GameObject;

//JSON��p���ăI�u�W�F�N�g���쐬����
namespace InstanceManager
{
	//������̗v�f�������邩
	const int INFO_STR = 3;
	const int INFO_FLOAT = 9;


	//JSON�̏��ŃI�u�W�F�N�g���쐬���邽�߂̍\����
	struct InstantiateInfoJSON
	{
		std::string parentName;			//�e�N���X
		std::string loadFile;			//�ǂݍ��މ摜
		std::string objectName;			//�ǂ�ȃI�u�W�F�N�g�𐶐����邩
		///////////////////////////////////////////////////////////////////
		XMFLOAT3 position;				//�ʒu
		XMFLOAT3 rotate;				//����
		XMFLOAT3 scale;					//�g�嗦
	};

	//JSONOpe�ɒl�S���ǂݏ����֐����������@InstantiateInfoJSON�̒��ɓ����@�Ă���

	//InstantiateInfoJSON��p���ăI�u�W�F�N�g���쐬����

	//�C���X�^���X�I�u�W�F�N�g�݂����Ȃ̂Ŋ����ł���悤��
};

