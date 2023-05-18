#include "JsonOperator.h"
#include <Windows.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../Json/rapidjson-master/include/rapidjson/stringbuffer.h"

using namespace rapidjson;

using std::string;
using std::vector;


namespace
{
    std::map<string, Document> dataList;
   // ("../Assets\\GameData\\TitleData.json");


    // JSON�t�@�C���̖��O
    const std::string TITLE_JSON = "../Assets\\GameData\\TitleScene.json";
   
}

namespace JsonOperator
{
    // ������
    void Initialize()
    {

    }

    //JSON�t�@�C����ǂݍ��ފ֐�
    bool LoadJSONFromFile(string filename, Document& document)
    {
        FILE* fp;
        if (fopen_s(&fp, filename.c_str(), "r") != 0)
        {
            MessageBox(NULL, "error", "BaseProjDx9�G���[", MB_OK);
        }

        // �t�@�C������ǂݍ���
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        document.ParseStream(is);

        // �t�@�C�������
        fclose(fp);

        // �ǂݍ��݂������������ǂ�����Ԃ�
        if (!document.HasParseError() && document.IsObject())
        {
            //�z��Ɋi�[
            //dataList.insert(std::make_pair(filename, document));
            return true;
        }
        return false;
    }

    //�t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
    bool LoadJSONString(std::string filename, std::string& str)
    {
        // JSON�t�@�C�����J��
        std::ifstream ifs(filename);
        if (!ifs) {
            return false;
        }

        // �t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
        std::string jsonStr((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        str = jsonStr;
        ifs.close();
    }

    //JSON�t�@�C���̕������ǂݎ��
    bool GetJSONString(std::string filename, std::string key, std::string& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        const char* name = "";
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsString()) {
            name = data[key.c_str()].GetString();
            out = name;
            return true;
        }
        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̐����l��ǂݎ��
    bool GetJSONInt(std::string filename, std::string key, int& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        int name = 0;
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsInt()) {
            name = data[key.c_str()].GetInt();
            out = name;
            return true;
        }
        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̐����l��ǂݎ��
    bool GetJSONFloat(std::string filename, std::string key, float& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        float name = 0.0f;
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsFloat()) {
            name = data[key.c_str()].GetFloat();
            out = name;
            return true;
        }
        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̕������ǂݎ��
    bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        const char* name = "";

        //�����̃Z�b�V���������邩�ǂ����m�F
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //�����̃L�[�����邩�ǂ����m�F
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsString()) {

                //�ǂݎ�����f�[�^������
                name = sectionData[key.c_str()].GetString();
                out = name;
                return true;
            }
        }

        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̐����l��ǂݎ��
    bool GetJSONInt(std::string filename, std::string section, std::string key, int& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        int name = 0.0f;

        //�����̃Z�b�V���������邩�ǂ����m�F
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //�����̃L�[�����邩�ǂ����m�F
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsInt()) {

                //�ǂݎ�����f�[�^������
                name = sectionData[key.c_str()].GetInt();
                out = name;
                return true;
            }
        }
        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̐����l��ǂݎ��
    bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        float name = 0.0f;

        //�����̃Z�b�V���������邩�ǂ����m�F
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //�����̃L�[�����邩�ǂ����m�F
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsFloat()) {

                //�ǂݎ�����f�[�^������
                name = sectionData[key.c_str()].GetFloat();
                out = name;
                return true;
            }
        }

        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���ɏ�������
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const std::string& value)
    {
        // JSON�I�u�W�F�N�g���쐬
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSON�Ƀf�[�^��ǉ�
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        rapidjson::GenericStringRef<char> val{ value.c_str() };
        keyDocument.AddMember(ref, val, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSON�𕶎��񉻂���
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSON���t�@�C���ɏ�������
        std::ofstream ofs(filename, std::ios::app);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const int& value)
    {
        //�w�肵���t�@�C�������������ꍇ
        if (dataList.find(filename) != end(dataList))
        {
            dataList[filename];
        }

        // JSON�I�u�W�F�N�g���쐬
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSON�Ƀf�[�^��ǉ�
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        keyDocument.AddMember(ref, value, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSON�𕶎��񉻂���
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSON���t�@�C���ɏ�������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    //JSON�t�@�C���ɏ�������(�㏑��)
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value)
    {
        // JSON�I�u�W�F�N�g���쐬
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSON�Ƀf�[�^��ǉ�
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        keyDocument.AddMember(ref, value, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSON�𕶎��񉻂���
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSON���t�@�C���ɏ�������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    // JSON�t�@�C���ɏ�������(�ǋL�A���������j
    bool AppendToJSONFileFloat(const std::string& filename, const std::string& section,const std::string& key, float value)
    { 
        //�t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
        std::string str = "";
        //���s������false��Ԃ�
        if (!LoadJSONString(filename, str))
        {
            return false;
        }

        // JSON�f�[�^���p�[�X����
        // �p�[�X�@�f�[�^����͂��K�v�ȃf�[�^�����o������
        Document document;
        //���s������false��Ԃ�
        if (document.Parse(str.c_str()).HasParseError()) {
            return false;
        }

        // �V�����l��ǉ��܂��͏㏑������
        if (!document.IsObject()) {
            return false;
        }

        // �I�u�W�F�N�g���Ɋ��ɓ����L�[�����݂���ꍇ�͏㏑���A�����łȂ��ꍇ�͒ǉ�����
        Document::AllocatorType& allocator = document.GetAllocator();
        if (document.HasMember(key.c_str())) {
            document[key.c_str()] = value;
        }
        else {
            Value newValueObj(value);
            document.AddMember(Value(key.c_str(), allocator).Move(), newValueObj, allocator);
        }

        // �X�V���ꂽJSON�f�[�^�𕶎���ɕϊ�����
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSON�t�@�C�����㏑������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }
}
//// JSON�z��̓ǂݍ��݂Ə���
   //if (document.HasMember("numbers") && document["numbers"].IsArray()) {
   //    const Value& numbersArray = document["numbers"];
   //    for (SizeType i = 0; i < numbersArray.Size(); i++) {
   //        if (numbersArray[i].IsNumber()) {
   //            double number = numbersArray[i].GetDouble();
   //            std::cout << "Number at index " << i << ": " << number << std::endl;
   //        }
   //    }
   //}


      // // �t�@�C�����J��
      // FILE* fp;
      // if (fopen_s(&fp, filename.c_str(), "r") != 0)
      // {
      //     MessageBox(NULL, "error", "BaseProjDx9�G���[", MB_OK);
      // }
      // // �t�@�C������ǂݍ���
      // string str;
      //// char readBuffer[65536];
      // FileReadStream is(fp, &str.front(), SHRT_MAX);
      // Document doc;
      // doc.ParseStream(is);
      // document.ParseStream(is);
      // dataList.insert(std::make_pair( list.at(filename), doc ));
      // // �t�@�C�������
      // if(fp != nullptr)
      //// fclose(fp);
      // // �ǂݍ��݂������������ǂ�����Ԃ�
      // return !document.HasParseError() && document.IsObject();
       // �t�@�C�����J��
