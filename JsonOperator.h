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
	/// JSON�t�@�C����ǂݍ��ފ֐�
	/// </summary>
	/// <param name="filename">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="document">�ǂݍ��ރh�L�������g</param>
	/// <returns>�����������ǂ���</returns>
	bool LoadJSONFromFile(const char* filename, Document& document);
	
	/// <summary>
	/// JSON�t�@�C���̕������ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="key">>�L�[�̖��O</param>
	/// <returns>�Ή����Ă��镶����</returns>
	std::string GetJSONString(std::string fileName, std::string key);
};

