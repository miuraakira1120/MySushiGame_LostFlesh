#pragma once

#include <string>
#include "../Json/rapidjson-master/include/rapidjson/document.h"
#include "../Json/rapidjson-master/include/rapidjson/filereadstream.h"
#include "../Json/rapidjson-master/include/rapidjson/filewritestream.h"
#include "../Json/rapidjson-master/include/rapidjson/writer.h"

using namespace rapidjson;

//JSON�̋L�q��
//https://products.sint.co.jp/topsic/blog/json#toc-2

namespace JsonOperator
{
	enum class JSONData
	{
		TITLE_DATA = 0,
		DATA_MAX
	};

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
	bool LoadJSONFromFile(std::string filename, Document& document);

	/// <summary>
	/// �t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
	/// </summary>
	/// <param name="filename">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="str">�ǂݍ��񂾕�����</param>
	/// <returns>�����������ǂ���</returns>
	bool LoadJSONString(std::string filename, std::string& str);

	/// <summary>
	/// �Z�b�V������ǉ�����֐�
	/// </summary>
	/// <param name="filename">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <returns>�����������ǂ���</returns>
	bool AddSection(const std::string& filename, const std::string& section);
	
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

	//////////////////////////////////////�Z�N�V��������i�I�[�o�[���[�h�j////////////////////////////////////////////

	/// <summary>
	/// JSON�t�@�C���̕������ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾕�����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out);

	/// <summary>
	/// JSON�t�@�C���̐����l��ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾐����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONInt(std::string filename, std::string section, std::string key, int& out);

	/// <summary>
	/// JSON�t�@�C���̏����l��ǂݎ��
	/// </summary>
	/// <param name="filename">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾏����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out);

	////////////////////////////��������(�㏑���j///////////////////////////////////////////////////

	/// <summary>
	/// JSON�t�@�C���ɏ�������
	/// </summary>
	/// <param name="filename">>�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�����l</param>
	/// <returns>�����������ǂ���</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string &section, const std::string &key, const std::string &value);

	/// <summary>
	/// JSON�t�@�C���ɏ�������
	/// </summary>
	/// <param name="filename">>�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�����l</param>
	/// <returns>�����������ǂ���</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string &section, const std::string &key, const int &value);

	/// <summary>
	/// JSON�t�@�C���ɏ�������(�㏑���j
	/// </summary>
	/// <param name="filename">>�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�����l</param>
	/// <returns>�����������ǂ���</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value);

	////////////////////////////��������(�ǋL�A���������j///////////////////////////////////////////////////

	/// <summary>
	/// JSON�t�@�C���ɏ�������(�ǋL�A���������j
	/// </summary>
	/// <param name="filename">�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�������ޒl</param>
	/// <returns>�����������ǂ���</returns>
	bool AppendToJSONFileString(const std::string& filename, const std::string& section, const std::string& key, std::string value);

	/// <summary>
	/// JSON�t�@�C���ɏ�������(�ǋL�A���������j
	/// </summary>
	/// <param name="filename">�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�������ޒl</param>
	/// <returns>�����������ǂ���</returns>
	bool AppendToJSONFileFloat(const std::string& filename, const std::string& section, const std::string& key, float value);


	/////////////////////////////////////////////////////////////////////////////////////////

//	template <class T = int>
//	bool GetData(const std::string& filename, const std::string& section, const std::string& key, T& out)
//	{
//		Document data;
//		//�t�@�C�����J���Ȃ�������false��Ԃ�
//		if (!LoadJSONFromFile(filename.c_str(), data))
//		{
//			return false;
//		}
//
//		//data�ɓǂݎ�����f�[�^������
//		int name = 0.0f;
//
//		//�����̃Z�N�V���������邩�ǂ����m�F
//		if (data.IsObject())
//		{
//			const Value& sectionData = data[section.c_str()];
//
//			//�����̃L�[�����邩�ǂ����m�F
//			if (sectionData.HasMember(key.c_str()) && (typeid(sectionData[key.c_str()]) == typeid(T))) {
//
//				//�ǂݎ�����f�[�^������
//				name = sectionData[key.c_str()].GetInt();
//				out = name;
//				return true;
//			}
//		}
//
//		//���s������false��Ԃ�
//		return false;
//	}
};

