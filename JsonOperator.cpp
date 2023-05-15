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
