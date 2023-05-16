#pragma once

#include <string>
#include "Json/rapidjson-master/include/rapidjson/document.h"
#include "Json/rapidjson-master/include/rapidjson/filereadstream.h"
#include "Json/rapidjson-master/include/rapidjson/filewritestream.h"
#include "Json/rapidjson-master/include/rapidjson/writer.h"

using namespace rapidjson;

//JSON�̋L�q��
//https://products.sint.co.jp/topsic/blog/json#toc-2

namespace JsonOperator
{
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

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
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾕�����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONString(std::string filename, std::string key, std::string &out);

	/// <summary>
	/// JSON�t�@�C���̐����l��ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾐����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONInt(std::string filename, std::string key, int &out);

	/// <summary>
	/// JSON�t�@�C���̏����l��ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾏����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONFloat(std::string filename, std::string key, float& out);

	//////////////////////////////////////�Z�b�V��������i�I�[�o�[���[�h�j////////////////////////////////////////////

	/// <summary>
	/// JSON�t�@�C���̕������ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�b�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾕�����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out);

	/// <summary>
	/// JSON�t�@�C���̐����l��ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�b�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾐����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONInt(std::string filename, std::string section, std::string key, int& out);

	/// <summary>
	/// JSON�t�@�C���̏����l��ǂݎ��
	/// </summary>
	/// <param name="filename">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�b�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾏����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out);


};

