#include "JsonOperator.h"
#include <Windows.h>


bool JsonOperator::LoadJSONFromFile(const char* filename, Document& document)
{
    // ファイルを開く
    FILE* fp;
    if (fopen_s(&fp, filename, "r") != 0) 
    {
        MessageBox(NULL, "error", "BaseProjDx9エラー", MB_OK);
    }

    // ファイルから読み込む
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    document.ParseStream(is);

    // ファイルを閉じる
    fclose(fp);

    // 読み込みが成功したかどうかを返す
    return !document.HasParseError() && document.IsObject();
}
