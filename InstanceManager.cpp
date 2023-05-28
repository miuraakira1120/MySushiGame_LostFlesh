#include "InstanceManager.h"
#include "Engine/JsonOperator.h"
#include "ChangeSceneButton.h"
#include "PlayerControlButton.h"

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

	Button* CreateButtonOnInfo(InstanceManager::InstantiateInfoJSON info, GameObject* parent)
	{
		ButtonManager::ButtonKinds infoObject = JsonOperator::StringToButton(info.parentName);

		//シーンチェンジボタンなら
		if (info.objectName == "sceneChangeButton")
		{
			//return InstantiateButton<ChangeSceneButton>(parent, info.loadFile, info.position, info.rotate, info.scale);
		}

		//プレイヤーコントロールボタンなら
		if (info.objectName == "playerControlButton")
		{
			return InstantiateButton<PlayerControlButton>(parent, info.loadFile, info.position, info.rotate, info.scale);
		}		
		return nullptr;
	}

	//JSONを用いてボタン生成する（メンバーすべて）
	bool AllCreateButton(std::string filename, std::vector<GameObject*>& pButtonList, GameObject* parent)
	{
		std::vector<GameObject*>resultList;
		//ファイル読み込み
		Document data;
		if (!JsonOperator::LoadJSONFromFile(filename, data))
		{
			return false;
		}
		
		if (!data.IsObject())
		{
			return false;
		}

		//読み取る
		int i = 0;
		std::vector <InstanceManager::InstantiateInfoJSON> infoList;
		for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
		{
			InstanceManager::InstantiateInfoJSON insInfo;
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
}