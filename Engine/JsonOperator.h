#pragma once

#include <string>
#include<vector>
#include <map>
#include <iostream>
#include <fstream>
#include "SceneManager.h"
#include "../Json/rapidjson-master/include/rapidjson/document.h"
#include "../Json/rapidjson-master/include/rapidjson/filereadstream.h"
#include "../Json/rapidjson-master/include/rapidjson/filewritestream.h"
#include "../Json/rapidjson-master/include/rapidjson/writer.h"
#include "../InstanceManager.h"


using namespace rapidjson;
class GameObject;


//JSON�̋L�q��
//https://products.sint.co.jp/topsic/blog/json#toc-2

namespace JsonOperator
{

	//////////////////////////////////////////////////////////////////////////////////////////////
	// �V�[���Ɋ֌W����萔
	// �g�p����JSON�t�@�C���̖��O
	//�e�X�g
	const std::string TEST_JSON = "../Assets\\GameData\\Test.json";
	
	//�^�C�g��
	const std::string TITLE_JSON = "../Assets\\GameData\\TitleScene.json";	
	const std::string TITLE_BUTTON_JSON = "../Assets\\GameData\\TitleButton.json";

	//////////////////////////////////////////////////////////////////////////////////////////////
	// �|�[�Y�Ɋ֌W����萔
	// �g�p����JSON�t�@�C���̖��O
	const std::string PAUSE_JSON = "../Assets\\GameData\\PauseScene.json";
	//////////////////////////////////////////////////////////////////////////////////////////////
	//�V�[���𕶎���ɂ������̒萔
	const std::vector<std::string> sceneStrList =
	{
		"playScene",
		"startScene",    
		"goalScene",
		"gameOverScene"
	};

	//���������\���̂���{�^���𕶎���ɂ������̒萔
	const std::vector<std::string> buttonStrList =
	{
		"sceneChangeButton",
		"playerControlButton"
	};

	//���������\���̂���I�u�W�F�N�g�𕶎���ɂ������̒萔
	


	/////////////////////////////////////////////////////////////////////////////////////////////////


	////�e�V�[���Ǝg�p����JSON�t�@�C���̖��O��R�t����
	//std::map<SCENE_ID, std::string> sceneFilename
	//{
	//	{SCENE_ID::SCENE_ID_START, TEST_JSON},
	//};

	///////////Instance�̂��߂̒萔/////////////////////////////////////////////////
	
	// �����������key(InstantiateInfoJSON�̗v�f�ɑΉ�������) 
	const std::vector<std::string> InstantiateKeyString =
	{
		"parentName",	//�e�N���X
     	"loadFile",		//�ǂݍ��މ摜
		"objectName"	//�ǂ�ȃI�u�W�F�N�g�𐶐����邩
	};	

	// �����������key(InstantiateInfoJSON�̗v�f�ɑΉ�������) 
	const std::vector<std::string> InstantiateKeyFloat =
	{
		"positionX",	//�ʒu
		"positionY",	//�ʒu
		"positionZ",	//�ʒu
		"rotateX",		//����
		"rotateY",		//����
		"rotateZ",		//����
		"scaleX",		//�g�嗦
		"scaleY",		//�g�嗦
		"scaleZ",		//�g�嗦
	};
	

	/////////////////////////////////////////////////////////////////////////


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
	/// JSON�t�@�C�����쐬����֐�
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// /// <returns>�����������ǂ���</returns>
	bool CreateJSONFile(std::string filename);

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

	/// ///////////////////////��������(�ǋL)///////////////////////////////////////////////////////////////


	//bool PostscriptJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value)

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	///////////////////////////////Instance�̂��߂̊֐�//////////////////////////////////////////////////////////


	/// <summary>
	/// �I�u�W�F�N�g�𐶐����邽�߂̏���JSON���珑������(������������)
	/// </summary>
	/// <param name="filename">�Z�N�V����</param>
	/// <param name="key">�L�[</param>
	/// <param name="info">�l������\����</param>
	/// <returns>�����������ǂ���</returns>
	bool WhiteInstanceInfo(const std::string& filename, const std::string& section, InstanceManager::InstantiateInfoJSON& info);

	/// <summary>
	/// �I�u�W�F�N�g�𐶐����邽�߂̏���JSON����ǂݍ���
	/// </summary>
	/// <param name="filename">�Z�N�V����</param>
	/// <param name="key">�L�[</param>
	/// <param name="info">�l������\����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetInstanceInfo(const std::string& filename, const std::string& section, InstanceManager::InstantiateInfoJSON& info);

	/// <summary>
	/// �d������������̌��ɐ���������v���O����
	/// </summary>
	/// <param name="filename">�������ރt�@�C���̖��O</param>
	/// <param name="unique"></param>
	/// 
	
	/// <summary>
	/// �d������������̌��ɐ���������v���O����
	/// </summary>
	/// <param name="filename">�������ރt�@�C���̖��O</param>
	/// <param name="str">���j�[�N�ɂ�����������</param>
	/// <returns>�����������ǂ���</returns>
	bool CreateUniqueNameJSON(std::string filename, std::string& str);

	/// <summary>
	/// �V�[���𕶎��ɕϊ�
	/// </summary>
	/// <param name="scene">������ɂ���V�[��</param>
	/// <returns>�ϊ�����������</returns>
	std::string SceneToString(SCENE_ID scene);

	/// <summary>
	/// �{�^���𕶎��ɕϊ�
	/// </summary>
	/// <param name="scene">������ɂ���{�^��</param>
	/// <returns>�ϊ�����������</returns>
	std::string ButtonToString(ButtonManager::ButtonKinds button);
	
	/// <summary>
	/// �������V�[���ɕϊ�
	/// </summary>
	/// <param name="scene">�V�[���ɂ��镶����</param>
	/// <returns>�ϊ������V�[��</returns>
	SCENE_ID StringToScene(std::string scene);

	
	/// <summary>
	/// �������{�^���ɕϊ�
	/// </summary>
	/// <param name="button">�{�^���ɂ��镶����</param>
	/// <returns></returns>
	ButtonManager::ButtonKinds StringToButton(std::string  button);

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

