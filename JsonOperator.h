#pragma once

#include <string>
#include "Json/rapidjson-master/include/rapidjson/document.h"
#include "Json/rapidjson-master/include/rapidjson/filereadstream.h"
#include "Json/rapidjson-master/include/rapidjson/filewritestream.h"
#include "Json/rapidjson-master/include/rapidjson/writer.h"

using namespace rapidjson;

//JSONの記述例
//https://products.sint.co.jp/topsic/blog/json#toc-2

namespace JsonOperator
{
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// JSONファイルを読み込む関数
	/// </summary>
	/// <param name="filename">読み込むファイルの名前</param>
	/// <param name="document">読み込むドキュメント</param>
	/// <returns>成功したかどうか</returns>
	bool LoadJSONFromFile(const char* filename, Document& document);
	
	/// <summary>
	/// JSONファイルの文字列を読み取る
	/// </summary>
	/// <param name="fileName">読み取るファイルの名前</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ文字列</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONString(std::string filename, std::string key, std::string &out);

	/// <summary>
	/// JSONファイルの整数値を読み取る
	/// </summary>
	/// <param name="fileName">読み取るファイルの名前</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ整数値</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONInt(std::string filename, std::string key, int &out);

	/// <summary>
	/// JSONファイルの小数値を読み取る
	/// </summary>
	/// <param name="fileName">読み取るファイルの名前</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ小数値</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONFloat(std::string filename, std::string key, float& out);

	//////////////////////////////////////セッションあり（オーバーロード）////////////////////////////////////////////

	/// <summary>
	/// JSONファイルの文字列を読み取る
	/// </summary>
	/// <param name="fileName">読み取るファイルの名前</param>
	/// <param name="section">セッション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ文字列</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out);

	/// <summary>
	/// JSONファイルの整数値を読み取る
	/// </summary>
	/// <param name="fileName">読み取るファイルの名前</param>
	/// <param name="section">セッション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ整数値</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONInt(std::string filename, std::string section, std::string key, int& out);

	/// <summary>
	/// JSONファイルの小数値を読み取る
	/// </summary>
	/// <param name="filename">読み取るファイルの名前</param>
	/// <param name="section">セッション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ小数値</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out);


};

