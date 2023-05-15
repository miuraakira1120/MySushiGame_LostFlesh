#pragma once

#include <string>
#include "Json/rapidjson-master/include/rapidjson/document.h"
#include "Json/rapidjson-master/include/rapidjson/filereadstream.h"
#include "Json/rapidjson-master/include/rapidjson/filewritestream.h"
#include "Json/rapidjson-master/include/rapidjson/writer.h"

using namespace rapidjson;

namespace JsonOperator
{
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
	/// <param name="key">>キーの名前</param>
	/// <returns>対応している文字列</returns>
	std::string GetJSONString(std::string fileName, std::string key);
};

