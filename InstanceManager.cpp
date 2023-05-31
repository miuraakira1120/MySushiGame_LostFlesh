#include "InstanceManager.h"
#include "Engine/JsonOperator.h"
#include "ChangeSceneButton.h"
#include "PlayerControlButton.h"
#include "ImageBase.h"
#include "Engine/JsonOperator.h"

namespace InstanceManager
{
	//JSON��p���ăI�u�W�F�N�g��ۑ�����i�Z�N�V���������j�[�N�ɂ���j
	bool SaveButton(std::string filename, std::string& section, std::string pathName, std::string objectName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
	{
		
		CreateInfoJSON info =
		{
			pathName,
			objectName,
			pos,
			rot,
			sca
		};

		//���j�[�N�ȃZ�N�V�����������
		std::string uniqueStr = section;
		if (!JsonOperator::CreateUniqueNameJSON(filename, uniqueStr))
		{
			return false;
		}

		//�����ɍ쐬�������j�[�N�Ȗ��O������
		section = uniqueStr;

		//JSON��Instantiate�ɕK�v�ȏ�����������
		JsonOperator::WhiteCreateInfo(filename, uniqueStr, info);

		return true;
	}

	//JSON��p���ăI�u�W�F�N�g���㏑���ۑ�����i�Z�N�V���������j�[�N�ɂ��Ȃ��j
	bool OverWriteSaveButton(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
	{
		std::string str;
		JsonOperator::GetJSONString(filename, section,JsonOperator::InstantiateKeyString[1], str);

		CreateInfoJSON info =
		{
			pathName,
			str,
			pos,
			rot,
			sca
		};

		//JSON��Instantiate�ɕK�v�ȏ�����������
		JsonOperator::WhiteCreateInfo(filename, section, info);

		return true;
	}

	//CreateInfoJSON�̏�����Ƀ{�^�����쐬����֐�
	Button* CreateButtonOnInfo(InstanceManager::CreateInfoJSON info, GameObject* parent)
	{
		//�V�[���`�F���W�{�^���Ȃ�
		if (info.objectName == "sceneChangeButton")
		{
			//return InstantiateButton<ChangeSceneButton>(parent, info.loadFile, info.position, info.rotate, info.scale);
		}

		//�v���C���[�R���g���[���{�^���Ȃ�
		if (info.objectName == "playerControlButton")
		{
			return InstantiateButton<PlayerControlButton>(parent, info.loadFile, info.position, info.rotate, info.scale);
		}		
		return nullptr;
	}

	//JSON��p���ă{�^����������i�����o�[���ׂāj
	bool AllCreateButton(std::string filename, std::vector<GameObject*>& pButtonList, GameObject* parent)
	{
		std::vector<GameObject*>resultList;
		//�t�@�C���ǂݍ���
		Document data;
		if (!JsonOperator::LoadJSONFromFile(filename, data))
		{
			return false;
		}
		
		if (!data.IsObject())
		{
			return false;
		}

		//�ǂݎ��
		int i = 0;
		std::vector <InstanceManager::CreateInfoJSON> infoList;
		for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
		{
			InstanceManager::CreateInfoJSON insInfo;
			JsonOperator::GetInstanceInfo(filename, it->name.GetString(), insInfo);
			infoList.push_back(insInfo);
			i++;
		}

		for (int i = 0; i < infoList.size(); i++)
		{
			resultList.push_back(CreateButtonOnInfo(infoList[i], parent));
		}

		pButtonList = resultList;

		return true;
	}

	// JSON��p���ĉ摜��ۑ�����i�Z�N�V���������j�[�N�ɂ���j
	bool SaveImage(std::string filename, std::string& section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha)
	{
		CreateImageInfoJSON info =
		{
			pathName,
			pos,
			rot,
			sca,
			alpha
		};

		//���j�[�N�ȃZ�N�V�����������
		std::string uniqueStr = section;
		if (!JsonOperator::CreateUniqueNameJSON(filename, uniqueStr))
		{
			return false;
		}

		//�����ɍ쐬�������j�[�N�Ȗ��O������
		section = uniqueStr;

		//JSON�ɉ摜��Instantiate�ɕK�v�ȏ�����������
		JsonOperator::WhiteCreateImageInfo(filename, section, info);

		return true;
	}

	// JSON��p���ĉ摜���㏑���ۑ�����i�Z�N�V���������j�[�N�ɂ��Ȃ��j
	bool OverWriteSaveImage(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
	{
		CreateImageInfoJSON info =
		{
			pathName,
			pos,
			rot,
			sca
		};

		//JSON��Instantiate�ɕK�v�ȏ�����������
		JsonOperator::WhiteCreateImageInfo(filename, section, info);

		return true;
	}

	// CreateInfoJSON�̏�����Ƀ{�^�����쐬����֐�
	GameObject* CreateImageOnInfo(InstanceManager::CreateImageInfoJSON info, GameObject* parent)
	{
		return InstantiateImage<ImageBase>(parent, info.loadFile, info.position, info.rotate, info.scale);
	}

	//JSON��p���ĉ摜�𐶐�����i�����o�[���ׂāj
	bool AllCreateImage(std::string filename, std::vector<GameObject*>& pImageList, GameObject* parent)
	{
		std::vector<GameObject*>resultList;
		//�t�@�C���ǂݍ���
		Document data;
		if (!JsonOperator::LoadJSONFromFile(filename, data))
		{
			return false;
		}

		if (!data.IsObject())
		{
			return false;
		}

		//�ǂݎ��
		int i = 0;
		std::vector <InstanceManager::CreateImageInfoJSON> infoList;
		for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
		{
			InstanceManager::CreateImageInfoJSON insInfo;
			JsonOperator::GetCreateImageInfo(filename, it->name.GetString(), insInfo);
			infoList.push_back(insInfo);
			i++;
		}

		for (int i = 0; i < infoList.size(); i++)
		{
			resultList.push_back(CreateImageOnInfo(infoList[i], parent));
		}

		pImageList = resultList;

		return true;
	}
}