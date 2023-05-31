#pragma once
#include <string>
#include <DirectXMath.h>
#include <vector>
#include "ButtonManager.h"
#include "Button.h"

using namespace DirectX;

class GameObject;

//JSONを用いてオブジェクトを作成する
namespace InstanceManager
{
	//文字列の要素が何個あるか
	const int INFO_STR = 2;
	const int INFO_FLOAT = 9;

	const std::string SUCCESS = "success";//成功したかどうかを判定する時に使う定数


	//JSONの情報でオブジェクトを作成するための構造体
	struct InstantiateInfoJSON
	{
		std::string loadFile;			//読み込む画像
		std::string objectName;			//どんなオブジェクトを生成するか
		///////////////////////////////////////////////////////////////////
		XMFLOAT3 position;				//位置
		XMFLOAT3 rotate;				//向き
		XMFLOAT3 scale;					//拡大率
	};

	//JSONOpeに値全部読み書き関数書きたい　InstantiateInfoJSONの中に入れる　てか上

	/// <summary>
	/// JSONを用いてオブジェクトを保存する
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名</param>
	/// <param name="info">生成する上で必要な情報</param>
	/// <returns>成功したかどうか</returns>
	
	/// <summary>
	/// JSONを用いてオブジェクトを保存する（セクションをユニークにする）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名(参照渡し)</param>
	/// <param name="pathName">読み込むファイルの名前</param>
	/// <param name="objectName">作るボタンの種類</param>
	/// <param name="pos">位置</param>
	/// <param name="rot">向き</param>
	/// <param name="sca">拡大率</param>
	/// <returns>成功したかどうか</returns>
	bool SaveButton(std::string filename, std::string& section, std::string pathName, std::string objectName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca);

	/// <summary>
	/// JSONを用いてオブジェクトを上書き保存する（セクションをユニークにしない）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名</param>
	/// <param name="pathName">読み込むファイルの名前</param>
	/// <param name="pos">位置</param>
	/// <param name="rot">向き</param>
	/// <param name="sca">拡大率</param>
	/// <returns></returns>
	bool OverwriteSaveButton(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca);

	/// <summary>
	/// InstantiateInfoJSONの情報を基にボタンを作成する関数
	/// </summary>
	/// <param name="info"></param>
	/// <returns></returns>
	Button* CreateButtonOnInfo(InstanceManager::InstantiateInfoJSON info, GameObject* parent);

	/// <summary>
	/// JSONを用いてボタン生成する（メンバーすべて）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="pButtonList">生成したボタンのポインタのリスト</param>
	/// <returns>成功したかどうか</returns>
	bool AllCreateButton(std::string filename, std::vector<GameObject*>& pButtonList, GameObject* parent);

};

