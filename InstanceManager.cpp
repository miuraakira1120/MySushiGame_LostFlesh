#include "InstanceManager.h"
#include "Engine/JsonOperator.h"

namespace InstanceManager
{
	bool SaveButton(std::string filename, std::string section, std::string parentStr, std::string pathName, std::string objectName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
	{
		
		InstantiateInfoJSON info =
		{
			parentStr,
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

		//JSON��Instantiate�ɕK�v�ȏ�����������
		JsonOperator::WhiteInstanceInfo(filename, uniqueStr, info);

		return true;
	}

	//JSON��p���ă{�^����������i�����o�[���ׂāj
	std::vector<GameObject*> AllCreateButton()
	{
		std::vector<GameObject*>list;
		//list.push_back(Instantiate<>);
		return list;
	}
}