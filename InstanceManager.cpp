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


		//ユニークなセクション名を作る
		std::string uniqueStr = section;
		if (!JsonOperator::CreateUniqueNameJSON(filename, uniqueStr))
		{
			return false;
		}

		//JSONにInstantiateに必要な情報を書き込む
		JsonOperator::WhiteInstanceInfo(filename, uniqueStr, info);

		return true;
	}

	//JSONを用いてボタン生成する（メンバーすべて）
	std::vector<GameObject*> AllCreateButton()
	{
		std::vector<GameObject*>list;
		//list.push_back(Instantiate<>);
		return list;
	}
}