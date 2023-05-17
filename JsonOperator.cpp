#include "JsonOperator.h"
#include <Windows.h>
#include <vector>
#include <map>
#include <fstream>

using std::string;
using std::vector;


namespace
{
    const std::map<string, JsonOperator::JSONData> list = {
        {"../Assets\\GameData\\TitleData.json", JsonOperator::JSONData::TITLE_DATA}
    };

    std::map<JsonOperator::JSONData, Document> dataList;
   // ("../Assets\\GameData\\TitleData.json");
   
}

namespace JsonOperator
{
    // 初期化
    void Initialize()
    {
      
    }

    //JSONファイルを読み込む関数
    bool LoadJSONFromFile(string filename, Document& document)
    {
        FILE* fp;
        if (fopen_s(&fp, filename.c_str(), "r") != 0)
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

    //JSONファイルに書き込む
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const std::string& value)
    {
        // JSONオブジェクトを作成
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSONにデータを追加
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();
        
        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        rapidjson::GenericStringRef<char> val{ value.c_str() };
        keyDocument.AddMember(ref, val, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSONを文字列化する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSONをファイルに書き込む
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const int& value)
    {
        // JSONオブジェクトを作成
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSONにデータを追加
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        keyDocument.AddMember(ref, value, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSONを文字列化する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSONをファイルに書き込む
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value)
    {
        // JSONオブジェクトを作成
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSONにデータを追加
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        keyDocument.AddMember(ref, value, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSONを文字列化する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSONをファイルに書き込む
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    //// JSON配列の読み込みと処理
    //if (document.HasMember("numbers") && document["numbers"].IsArray()) {
    //    const Value& numbersArray = document["numbers"];
    //    for (SizeType i = 0; i < numbersArray.Size(); i++) {
    //        if (numbersArray[i].IsNumber()) {
    //            double number = numbersArray[i].GetDouble();
    //            std::cout << "Number at index " << i << ": " << number << std::endl;
    //        }
    //    }
    //}


       // // ファイルを開く
       // FILE* fp;
       // if (fopen_s(&fp, filename.c_str(), "r") != 0)
       // {
       //     MessageBox(NULL, "error", "BaseProjDx9エラー", MB_OK);
       // }
       // // ファイルから読み込む
       // string str;
       //// char readBuffer[65536];
       // FileReadStream is(fp, &str.front(), SHRT_MAX);
       // Document doc;
       // doc.ParseStream(is);
       // document.ParseStream(is);
       // dataList.insert(std::make_pair( list.at(filename), doc ));
       // // ファイルを閉じる
       // if(fp != nullptr)
       //// fclose(fp);
       // // 読み込みが成功したかどうかを返す
       // return !document.HasParseError() && document.IsObject();
        // ファイルを開く

}

