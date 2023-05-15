#include "JsonOperator.h"
#include <Windows.h>


bool JsonOperator::LoadJSONFromFile(const char* filename, Document& document)
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

std::string JsonOperator::GetJSONString(std::string fileName, std::string key)
{
    Document data;
    bool isSuccess = JsonOperator::LoadJSONFromFile(fileName.c_str(), data);

    const char* name = "";
    if (data.HasMember(key.c_str()) && data[key.c_str()].IsString()) {
        name = data[key.c_str()].GetString();
    }
    return name;
}

