#pragma once
#include <string>
#include <DirectXMath.h>

using namespace DirectX;

class GameObject;

//JSONを用いてオブジェクトを作成する
namespace InstanceManager
{
	//文字列の要素が何個あるか
	const int INFO_STR = 3;
	const int INFO_FLOAT = 9;


	//JSONの情報でオブジェクトを作成するための構造体
	struct InstantiateInfoJSON
	{
		std::string parentName;			//親クラス
		std::string loadFile;			//読み込む画像
		std::string objectName;			//どんなオブジェクトを生成するか
		///////////////////////////////////////////////////////////////////
		XMFLOAT3 position;				//位置
		XMFLOAT3 rotate;				//向き
		XMFLOAT3 scale;					//拡大率
	};

	//JSONOpeに値全部読み書き関数書きたい　InstantiateInfoJSONの中に入れる　てか上

	//InstantiateInfoJSONを用いてオブジェクトを作成する

	//インスタンスオブジェクトみたいなので完結できるように
};

