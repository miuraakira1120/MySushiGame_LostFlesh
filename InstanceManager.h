#pragma once
#include <string>
#include <DirectXMath.h>
#include <vector>
#include "ButtonManager.h"
#include "Button.h"

using namespace DirectX;

class GameObject;

//JSON��p���ăI�u�W�F�N�g���쐬����
namespace InstanceManager
{
	//������̗v�f�������邩
	const int INFO_STR = 2;
	const int INFO_FLOAT = 9;

	const std::string SUCCESS = "success";//�����������ǂ����𔻒肷�鎞�Ɏg���萔


	//JSON�̏��ŃI�u�W�F�N�g���쐬���邽�߂̍\����
	struct InstantiateInfoJSON
	{
		std::string loadFile;			//�ǂݍ��މ摜
		std::string objectName;			//�ǂ�ȃI�u�W�F�N�g�𐶐����邩
		///////////////////////////////////////////////////////////////////
		XMFLOAT3 position;				//�ʒu
		XMFLOAT3 rotate;				//����
		XMFLOAT3 scale;					//�g�嗦
	};

	//JSONOpe�ɒl�S���ǂݏ����֐����������@InstantiateInfoJSON�̒��ɓ����@�Ă���

	/// <summary>
	/// JSON��p���ăI�u�W�F�N�g��ۑ�����
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="info">���������ŕK�v�ȏ��</param>
	/// <returns>�����������ǂ���</returns>
	
	/// <summary>
	/// JSON��p���ăI�u�W�F�N�g��ۑ�����i�Z�N�V���������j�[�N�ɂ���j
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������(�Q�Ɠn��)</param>
	/// <param name="pathName">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="objectName">���{�^���̎��</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="rot">����</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>�����������ǂ���</returns>
	bool SaveButton(std::string filename, std::string& section, std::string pathName, std::string objectName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca);

	/// <summary>
	/// JSON��p���ăI�u�W�F�N�g���㏑���ۑ�����i�Z�N�V���������j�[�N�ɂ��Ȃ��j
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="pathName">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="rot">����</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns></returns>
	bool OverwriteSaveButton(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca);

	/// <summary>
	/// InstantiateInfoJSON�̏�����Ƀ{�^�����쐬����֐�
	/// </summary>
	/// <param name="info"></param>
	/// <returns></returns>
	Button* CreateButtonOnInfo(InstanceManager::InstantiateInfoJSON info, GameObject* parent);

	/// <summary>
	/// JSON��p���ă{�^����������i�����o�[���ׂāj
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="pButtonList">���������{�^���̃|�C���^�̃��X�g</param>
	/// <returns>�����������ǂ���</returns>
	bool AllCreateButton(std::string filename, std::vector<GameObject*>& pButtonList, GameObject* parent);

};

