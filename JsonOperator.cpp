#include "JsonOperator.h"
#include <Windows.h>
namespace
{
    Document data;
    const std::string filename = "test.json";
}

namespace JsonOperator
{

    // ������
    void Initialize()
    {
        //JSON�t�@�C����ǂݍ��ފ֐�
        LoadJSONFromFile(filename.c_str(), data);

        //�ǂݍ��݂����s������
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            MessageBox(NULL, "�ǂݍ��݂��������Ȃ�����", "BaseProjDx9�G���[", MB_OK);
        }
    }

    //JSON�t�@�C����ǂݍ��ފ֐�
    bool LoadJSONFromFile(const char* filename, Document& document)
    {
        // �t�@�C�����J��
        FILE* fp;
        if (fopen_s(&fp, filename, "r") != 0)
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
        return !document.HasParseError() && document.IsObject();
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

}

