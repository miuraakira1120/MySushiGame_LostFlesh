#include "JsonOperator.h"
#include <Windows.h>
namespace
{
    Document data;
    const std::string filename = "test.json";
}

namespace JsonOperator
{

    // 初期化
    void Initialize()
    {
        //JSONファイルを読み込む関数
        LoadJSONFromFile(filename.c_str(), data);

        //読み込みが失敗したら
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            MessageBox(NULL, "読み込みが成功しなかった", "BaseProjDx9エラー", MB_OK);
        }
    }

    //JSONファイルを読み込む関数
    bool LoadJSONFromFile(const char* filename, Document& document)
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

    //JSONファイルの文字列を読み取る
    bool GetJSONString(std::string filename, std::string key, std::string& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        const char* name = "";
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsString()) {
            name = data[key.c_str()].GetString();
            out = name;
            return true;
        }
        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの整数値を読み取る
    bool GetJSONInt(std::string filename, std::string key, int& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        int name = 0;
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsInt()) {
            name = data[key.c_str()].GetInt();
            out = name;
            return true;
        }
        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの整数値を読み取る
    bool GetJSONFloat(std::string filename, std::string key, float& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        float name = 0.0f;
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsFloat()) {
            name = data[key.c_str()].GetFloat();
            out = name;
            return true;
        }
        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの文字列を読み取る
    bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        const char* name = "";

        //引数のセッションがあるかどうか確認
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //引数のキーがあるかどうか確認
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsString()) {

                //読み取ったデータを入れる
                name = sectionData[key.c_str()].GetString();
                out = name;
                return true;
            }
        }

        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの整数値を読み取る
    bool GetJSONInt(std::string filename, std::string section, std::string key, int& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        int name = 0.0f;

        //引数のセッションがあるかどうか確認
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //引数のキーがあるかどうか確認
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsInt()) {

                //読み取ったデータを入れる
                name = sectionData[key.c_str()].GetInt();
                out = name;
                return true;
            }
        }

        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの整数値を読み取る
    bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        float name = 0.0f;

        //引数のセッションがあるかどうか確認
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //引数のキーがあるかどうか確認
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsFloat()) {

                //読み取ったデータを入れる
                name = sectionData[key.c_str()].GetFloat();
                out = name;
                return true;
            }
        }

        //失敗したらfalseを返す
        return false;
    }

}

