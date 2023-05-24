#pragma once

#include <string>
#include "../Json/rapidjson-master/include/rapidjson/document.h"
#include "../Json/rapidjson-master/include/rapidjson/filereadstream.h"
#include "../Json/rapidjson-master/include/rapidjson/filewritestream.h"
#include "../Json/rapidjson-master/include/rapidjson/writer.h"

using namespace rapidjson;

//JSONの記述例
//https://products.sint.co.jp/topsic/blog/json#toc-2

namespace JsonOperator
{
	enum class JSONData
	{
		TITLE_DATA = 0,
		DATA_MAX
	};

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
	bool LoadJSONFromFile(std::string filename, Document& document);

	/// <summary>
	/// ファイルの内容を文字列として読み込む
	/// </summary>
	/// <param name="filename">読み込むファイルの名前</param>
	/// <param name="str">読み込んだ文字列</param>
	/// <returns>成功したかどうか</returns>
	bool LoadJSONString(std::string filename, std::string& str);

	/// <summary>
	/// セッションを追加する関数
	/// </summary>
	/// <param name="filename">読み込むファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <returns>成功したかどうか</returns>
	bool AddSection(const std::string& filename, const std::string& section);
	
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

	//////////////////////////////////////セクションあり（オーバーロード）////////////////////////////////////////////

	/// <summary>
	/// JSONファイルの文字列を読み取る
	/// </summary>
	/// <param name="fileName">読み取るファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ文字列</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out);

	/// <summary>
	/// JSONファイルの整数値を読み取る
	/// </summary>
	/// <param name="fileName">読み取るファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ整数値</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONInt(std::string filename, std::string section, std::string key, int& out);

	/// <summary>
	/// JSONファイルの小数値を読み取る
	/// </summary>
	/// <param name="filename">読み取るファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="out">読み込んだ小数値</param>
	/// <returns>成功したかどうか</returns>
	bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out);

	////////////////////////////書き込み(上書き）///////////////////////////////////////////////////

	/// <summary>
	/// JSONファイルに書き込む
	/// </summary>
	/// <param name="filename">>書き込むファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="value">入れる値</param>
	/// <returns>成功したかどうか</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string &section, const std::string &key, const std::string &value);

	/// <summary>
	/// JSONファイルに書き込む
	/// </summary>
	/// <param name="filename">>書き込むファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="value">入れる値</param>
	/// <returns>成功したかどうか</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string &section, const std::string &key, const int &value);

	/// <summary>
	/// JSONファイルに書き込む(上書き）
	/// </summary>
	/// <param name="filename">>書き込むファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="value">入れる値</param>
	/// <returns>成功したかどうか</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value);

	////////////////////////////書き込み(追記、書き換え）///////////////////////////////////////////////////

	/// <summary>
	/// JSONファイルに書き込む(追記、書き換え）
	/// </summary>
	/// <param name="filename">書き込むファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="value">書き込む値</param>
	/// <returns>成功したかどうか</returns>
	bool AppendToJSONFileString(const std::string& filename, const std::string& section, const std::string& key, std::string value);

	/// <summary>
	/// JSONファイルに書き込む(追記、書き換え）
	/// </summary>
	/// <param name="filename">書き込むファイルの名前</param>
	/// <param name="section">セクション名</param>
	/// <param name="key">キーの名前</param>
	/// <param name="value">書き込む値</param>
	/// <returns>成功したかどうか</returns>
	bool AppendToJSONFileFloat(const std::string& filename, const std::string& section, const std::string& key, float value);


	/////////////////////////////////////////////////////////////////////////////////////////

//	template <class T = int>
//	bool GetData(const std::string& filename, const std::string& section, const std::string& key, T& out)
//	{
//		Document data;
//		//ファイルを開けなかったらfalseを返す
//		if (!LoadJSONFromFile(filename.c_str(), data))
//		{
//			return false;
//		}
//
//		//dataに読み取ったデータを入れる
//		int name = 0.0f;
//
//		//引数のセクションがあるかどうか確認
//		if (data.IsObject())
//		{
//			const Value& sectionData = data[section.c_str()];
//
//			//引数のキーがあるかどうか確認
//			if (sectionData.HasMember(key.c_str()) && (typeid(sectionData[key.c_str()]) == typeid(T))) {
//
//				//読み取ったデータを入れる
//				name = sectionData[key.c_str()].GetInt();
//				out = name;
//				return true;
//			}
//		}
//
//		//失敗したらfalseを返す
//		return false;
//	}
};

