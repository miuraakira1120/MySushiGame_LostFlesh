#pragma once
#include <string>
#include <DirectXMath.h>

using namespace DirectX;

class GameObject;

//JSONを用いてオブジェクトを作成する
namespace InstanceManager
{
	//JSONの情報でオブジェクトを作成するための構造体
	struct InstantiateInfoJSON
	{
		GameObject* parent;				//親クラス
		std::string loadFile;			//読み込む画像
		XMFLOAT3 position;		//位置
		XMFLOAT3 rotate;		//向き
		XMFLOAT3 scale;		//拡大率
		GameObject* object;				//どんなオブジェクトを生成するか
	};


	/// <summary>
	/// オブジェクトを生成するための情報をJSONから読み込む
	/// </summary>
	/// <param name="filename">セクション</param>
	/// <param name="key">キー</param>
	/// <param name="info">値を入れる構造体</param>
	/// <returns>成功したかどうか</returns>
	bool GetInstanceInfo(std::string filename, std::string key, InstantiateInfoJSON& info);

	//JSONOpeに値全部取る関数書きたい　InstantiateInfoJSONの中に入れる　てか上

	//InstantiateInfoJSONを用いてオブジェクトを作成する

	//インスタンスオブジェクトみたいなので完結できるように
};

