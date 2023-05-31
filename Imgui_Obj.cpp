#include "Imgui_Obj.h"
#include "imgui/imgui.h"
#include "Time.h"
#include "Engine/JsonOperator.h"

#include "Engine/GameObject.h"
#include "Maguro.h"
#include "Syari.h"
#include "Engine/Text.h"
#include "ChangeSceneButton.h"
#include "PlayerControlButton.h"
#include "Engine/SceneManager.h"
#include "Engine/Math.h"
#include "Engine/Input.h"

#include "Pause.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "GameManager.h"

//何のクラスを作成するか
enum class IniType
{
    NONE,
    BUTTON,
    ENEMY,
    TYPE_MAX

};

namespace
{
    Text* pText;
    int gameTimerID;
    ChangeSceneButton* pChangeSceneButton;
    SceneManager* pSceneManager;

    float changeSceneButtonX;
    float changeSceneButtonY;

    int iniListButton;//タイトルシーンのボタンの番号

    //使用するiniファイルの名前
    const std::string iniFileName = "UI.ini";

    //char型の配列のサイズ(2の8乗)
    const int CHAR_SIZE = 256;

    //親を何にするか
    int parentNum;

    int buttonKinds = static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);//ボタンの種類

    IniType iniType = IniType::NONE;

    int nextScene;//次に行くシーン
    int SceneChangeNextScene; //SceneChangeの時に使う次に行くシーン

    std::string selectUniqueName;//選択中のオブジェクトのユニークな名前
    
    GameObject* pSelectObj;//選択中のオブジェクト
    std::string selectButtonKinds;//選択中のオブジェクトの種類
    string selectLoadFileNameStr;//選択中のオブジェクトが読み込む画像やモデルのファイル名

    char loadFileName[CHAR_SIZE] = "";//読み込むファイル名
    char sectionName[CHAR_SIZE];//セクションの名前 
    XMFLOAT3 iniPosition = { 0,0,0 };//位置
    XMFLOAT3 iniScale = { 1,1,1 };//拡大率
    XMFLOAT3 iniRotate = { 0,0,0 };//向き
    std::string selectWriteFile;//選択中のオブジェクトが保存をする際に書き込んだJSONのファイル名

    //再設定の時に必要な情報
    struct SettingInfo
    {
        SettingInfo(GameObject* obj, std::string loadFileName, std::string sectionName, std::string writeFileName, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 rotate) :
            pObject{ obj },loadFileName { loadFileName }, sectionName{ sectionName }, writeFile{ writeFileName }, iniPosition
            {position}, iniRotate{ rotate }, iniScale{ scale } {}

        GameObject* pObject;
        std::string loadFileName = "";//読み込むファイル名
        std::string sectionName;//セクションの名前 
        std::string writeFile;//保存をする際に書き込んだJSONのファイル名
        XMFLOAT3 iniPosition;//位置
        XMFLOAT3 iniRotate;//向き
        XMFLOAT3 iniScale;//拡大率

    };

    std::vector<SettingInfo> settingInfoList;//作ったボタンのリスト 
    
}

namespace Imgui_Obj
{
    //初期化
    void Initialize(SceneManager* pSceneManager_)
    {
        pText = new Text;
        pText->Initialize();
        pSceneManager = pSceneManager_;
    }

    //更新
    void Update()
    {
        pChangeSceneButton = (ChangeSceneButton*)pSceneManager->FindObject("ChangeSceneButton");

        //Imguiを生成する
        InstantiateImgui();
        
    }

    //開放
    void Release()
    {
        pText->Release();
    }

    //Imguiを生成する
    void InstantiateImgui()
    {
        //作成用のImguiを出す
        ImguiIniObj();

        //作ったオブジェクトの再設定を出来るようにする
        ReSettingButton();

        //楽にシーンチェンジ出来るようにする
        SceneChangeImgui();

        //タイトルシーンだったら
        if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_START)
        {
            ///////////////////////ボタンの位置////////////////////////////////////////

            ImGui::Begin("Botton Pos");
            //////////////////////スタートボタン/////////////////////////////////////////////////////

            static float testFloat;
            ImGui::InputFloat("x", &testFloat, -1, 1);

            if (ImGui::Button("MouseModeON"))
            {
                pChangeSceneButton->MouseModeON();
            }
            if (ImGui::Button("MouseModeOFF"))
            {
                pChangeSceneButton->MouseModeOFF();
            }

            ImGui::SliderFloat("ChangeSceneButtonX", &changeSceneButtonX, -1.0f, 1.0f);
            ImGui::SliderFloat("ChangeSceneButtonY", &changeSceneButtonY, -1.0f, 1.0f);

            //マウスモードならシリンダーで位置が変わらない変わらない
            if (!pChangeSceneButton->GetMouseMode())
            {
                //シリンダーいじるまでは変わらない
                if (!changeSceneButtonX == 0 || !changeSceneButtonY == 0)
                {
                    //ボタンの位置を変える
                    pChangeSceneButton->SetPosition(changeSceneButtonX, changeSceneButtonY, 0);
                }
            }
            else
            {
                //マウスモードかつボタンが選ばれてなおかつ左クリックが押されていたら
                if (pChangeSceneButton->GetValue() && Input::IsMouseButton(1))
                {
                    pChangeSceneButton->SetPosition(Math::PixelToTransform(Input::GetMousePosition()));
                }
            }

            //ボタンの位置のセーブ
            if (ImGui::Button("PositionSave"))
            {
                JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posX", pChangeSceneButton->GetPosition().x);
                JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posY", pChangeSceneButton->GetPosition().y);
            }

            ImGui::End();
        }
    }

    void Draw()
    {
        //{
        //    //Imguiスタート
        //    ImGui_ImplDX11_NewFrame();
        //    ImGui_ImplWin32_NewFrame();
        //    ImGui::NewFrame();

        //    //window作る
        //    ImGui::Begin("StageCreater", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        //    ImGui::End();
        //}
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    //オブジェクトを生成するImguiを出す関数
    void ImguiIniObj()
    {
        //Pause SettingのImguiを作成
        ImGui::Begin("Pause Setting");
        if (ImGui::TreeNode("Instantiate"))
        {
            if (ImGui::Button("Button"))
            {
                iniType = IniType::BUTTON;
            }
            if (ImGui::Button("Enemy"))
            {
                iniType = IniType::ENEMY;
            }
            ImGui::TreePop();

            //ボタン作成モードなら
            if (iniType == IniType::BUTTON)
            {
                ImGui::Begin("Button Instantiate");

                //セクション名
                ImGui::Text("ObjectName");
                ImGui::InputText("name", sectionName, CHAR_SIZE);
                selectUniqueName = sectionName;

                //読み込むファイル名を入力
                ImGui::Text("LoadFileName");
                ImGui::InputText(".png", loadFileName, CHAR_SIZE);

                //Transfomの情報を入力
                ImGui::Text("Transform");

                //位置
                float speed = 0.05f;
                //参照で生成
                float* iniPositionArray[3] = { &iniPosition.x, &iniPosition.y, &iniPosition.z };
                ImGui::DragFloat3("Position", iniPositionArray[0], speed, -1.0f, 1.0f);

                //向き
                float* iniRotateArray[3] = { &iniRotate.x,&iniRotate.y, &iniRotate.z };
                ImGui::DragFloat3("Rotate", iniRotateArray[0], speed, -1.0f, 1.0f);

                //拡大率
                float* iniScaleArray[3] = { &iniScale.x,&iniScale.y, &iniScale.z };
                ImGui::DragFloat3("Scale", iniScaleArray[0], speed, -1.0f, 1.0f);

                //どんな種類のボタンを生成するか
                ImGui::Text("ButtonType");
                //ImGui::RadioButton("SceneChange", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON)); ImGui::SameLine();
                ImGui::RadioButton("PlayerControl", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON)); 

                //シーンチェンジボタンを作成する予定なら
                if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON))
                {
                    ImGui::Text("NextScene");
                    ImGui::RadioButton("Title", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
                    ImGui::RadioButton("Play", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
                    ImGui::RadioButton("GameOver", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER)); ImGui::SameLine();
                    ImGui::RadioButton("Clear", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL));
                }

                //親オブジェクトは何か(どこで生成するか)
                ImGui::Text("Parent");
                ImGui::RadioButton("NowScene", &parentNum, static_cast<int>(GameManager::ParentNum::NOW_SCENE)); ImGui::SameLine();
                ImGui::RadioButton("Pause", &parentNum, static_cast<int>(GameManager::ParentNum::PAUSE));               

                //生成ボタン
                if (ImGui::Button("Instantiate"))
                {

                    //シーンチェンジボタンを作成するなら
                    if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON))
                    {

                    }

                    //プレイヤーのボタン配置を変えるボタンを作成するなら
                    if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON))
                    {
                        selectButtonKinds = JsonOperator::ButtonToString(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);

                        //拡張子にpngを追加
                        selectLoadFileNameStr = loadFileName;
                        selectLoadFileNameStr += ".png";

                        //保存していないオブジェクトは消す
                        if (pSelectObj != nullptr)
                        {
                            pSelectObj->KillMe();
                        }

                        //親が今のシーンなら
                        if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                        {    
                            //生成
                            pSelectObj = InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
                        }

                        //親がポーズなら
                        if (parentNum == static_cast<int>(GameManager::ParentNum::PAUSE))
                        {

                        }

                        //親がプレイヤーなら
                        if (parentNum == static_cast<int>(GameManager::ParentNum::PLAYER))
                        {

                        }
                       
                    }
                } 

                if (pSelectObj != nullptr)
                {
                    ImGui::SameLine();
                    //セーブボタン
                    if (ImGui::Button("Save"))
                    {
                        //タイトルシーンだったら
                        switch (pSceneManager->GetNowSceneID())
                        {
                            //タイトルシーンだったら
                        case SCENE_ID::SCENE_ID_START:
                            InstanceManager::SaveButton(JsonOperator::TITLE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                            break;
                        default:
                            break;
                        }
                        //事後
                        RearButtonInstantiate();

                    }ImGui::SameLine();

                    //削除ボタン
                    if (ImGui::Button("Delete"))
                    {
                        pSelectObj->KillMe();
                        pSelectObj = nullptr;
                    }
                }

                //キャンセルボタン
                if (ImGui::Button("Cancel"))
                {

                    iniType = IniType::NONE;
                }
                ImGui::End();
            }
        }
        ImGui::End();
    }

    //シーンチェンジするImguiを生成する関数
    void SceneChangeImgui()
    {
        ImGui::Begin("Scene Change");
        ImGui::RadioButton("Title", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
        ImGui::RadioButton("Play", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
        ImGui::RadioButton("Goal", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL)); ImGui::SameLine();
        ImGui::RadioButton("GameOver", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER));

        if (ImGui::Button("Scene Change"))
        {
            pSceneManager->ChangeScene(static_cast<SCENE_ID>(nextScene));
        }
        ImGui::End();
    }

    //imguiでボタンを保存した後にやること
    void RearButtonInstantiate()
    {
        SettingInfo setting{ pSelectObj, selectLoadFileNameStr, selectUniqueName , selectWriteFile,iniPosition, iniRotate, iniScale };
        settingInfoList.push_back(setting);
        pSelectObj = nullptr;
    }

    //作ったボタンの再移動等を出来るようにする
    void ReSettingButton()
    {
        //ボタン
        {
            //pCreateListの分だけ回す
            for (int i = 0; i < settingInfoList.size(); i++)
            {
                ImGui::Begin(settingInfoList[i].sectionName.c_str());

                //読み込むファイル名を入力
                ImGui::Text("LoadFileName");
                char sec[CHAR_SIZE];
                settingInfoList[i].loadFileName.copy(sec, CHAR_SIZE - 1);
                sec[settingInfoList[i].loadFileName.length()] = '\0';
                ImGui::InputText("LoadFile", sec, CHAR_SIZE);
                settingInfoList[i].loadFileName = sec;
                if (ImGui::Button("Decision"))
                {
                    settingInfoList[i].pObject->SetPathName(loadFileName);
                }

                //Transfomの情報を入力
                ImGui::Text("Transform");
                float speed = 0.05f;
                //位置
                float* iniPositionArrayTmp[3] = { &settingInfoList[i].iniPosition.x, &settingInfoList[i].iniPosition.y, &settingInfoList[i].iniPosition.z };
                ImGui::DragFloat3("Position", iniPositionArrayTmp[0], speed, -1.0f, 1.0f);
                settingInfoList[i].pObject->SetPosition(settingInfoList[i].iniPosition);

                //向き
                float* iniRotateArrayTmp[3] = { &settingInfoList[i].iniRotate.x,&settingInfoList[i].iniRotate.y, &settingInfoList[i].iniRotate.z };
                ImGui::DragFloat3("Rotate", iniRotateArrayTmp[0], speed, -1.0f, 1.0f);
                settingInfoList[i].pObject->SetRotate(settingInfoList[i].iniRotate);

                //拡大率
                float* iniScaleArrayTmp[3] = { &settingInfoList[i].iniScale.x,&settingInfoList[i].iniScale.y, &settingInfoList[i].iniScale.z };
                ImGui::DragFloat3("Scale", iniScaleArrayTmp[0], speed, -1.0f, 1.0f);
                settingInfoList[i].pObject->SetScale(settingInfoList[i].iniScale);

                //保存
                if (ImGui::Button("Save"))
                {
                    InstanceManager::OverwriteSaveButton(
                        settingInfoList[i].writeFile,
                        settingInfoList[i].sectionName,
                        settingInfoList[i].loadFileName, 
                        settingInfoList[i].iniPosition, 
                        settingInfoList[i].iniRotate, 
                        settingInfoList[i].iniScale);
                }
                //削除
                if (ImGui::Button("Delete"))
                {
                    settingInfoList[i].pObject->KillMe();

                }

                ImGui::End();
            }
        }
        //オブジェクト
        {

        }
    }
}



//TREENODE
//TreePop

//
//ImGui::Begin("Test Window");
//
//ImGui::Text("Hello, world %d", 123);
//
////if (ImGui::Button("オブジェクトを追加")) 
////{
////    printf("Button\n");
////}
//
//static char buf[256] = "";
//if (ImGui::InputText("string", buf, 256)) {
//    printf("InputText\n");
//}
//
//static float f = 0.0f;
//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
