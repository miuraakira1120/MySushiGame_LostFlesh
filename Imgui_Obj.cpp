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

    //親を何にするか
    int parentNum;

    int buttonKinds = static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);//ボタンの種類

    IniType iniType = IniType::NONE;

    int nextScene;//次に行くシーン
    int SceneChangeNextScene; //SceneChangeの時に使う次に行くシーン

    
    GameObject* pSelectObj;//選択中のオブジェクト
    std::string selectButtonKinds;//選択中のオブジェクトの種類
    string selectLoadFileNameStr;//選択中のオブジェクトが読み込む画像やモデルのファイル名

    char loadFileName[256] = "";//読み込むファイル名
    char sectionName[256];//セクションの名前 
    XMFLOAT3 iniPosition = { 0,0,0 };//位置
    XMFLOAT3 iniScale = { 1,1,1 };//拡大率
    XMFLOAT3 iniRotate = { 0,0,0 };//向き

    //再設定したい情報
    struct SettingInfo
    {
        SettingInfo(std::string loadFileName, std::string sectionName, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 rotate) :
            loadFileName{ loadFileName }, sectionName{ sectionName }, iniPosition{ position }, iniScale{ scale }, iniRotate{ rotate } {}

        std::string loadFileName = "";//読み込むファイル名
        std::string sectionName;//セクションの名前 
        XMFLOAT3 iniPosition;//位置
        XMFLOAT3 iniScale;//拡大率
        XMFLOAT3 iniRotate;//向き
    };

    std::vector<GameObject*> pCreateList;//作ったオブジェクトのリスト
    std::vector<SettingInfo> settingInfoList;//pCreateListに対応させるリスト 
    
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
        ReSetting();

        //楽にシーンチェンジ出来るようにする
        SceneChangeImgui();

        //タイトルシーンだったら
        if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_START)
        {
            ///////////////////////ボタンの位置////////////////////////////////////////

            ImGui::Begin("Botton Pos");
            //////////////////////スタートボタン/////////////////////////////////////////////////////


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
                ImGui::InputText("name", sectionName, 256);

                //読み込むファイル名を入力
                ImGui::Text("LoadFileName");
                ImGui::InputText(".png", loadFileName, 256);               

                //Transfomの情報を入力
                ImGui::Text("Transform");

                //位置
                //参照で生成
                float* iniPositionArray[3] = { &iniPosition.x, &iniPosition.y, &iniPosition.z };
                ImGui::InputFloat3("Position", iniPositionArray[0]);

                //向き
                float* iniRotateArray[3] = { &iniRotate.x,&iniRotate.y, &iniRotate.z };
                ImGui::InputFloat3("Rotate", iniRotateArray[0]);

                //拡大率
                float* iniiniScaleArray[3] = { &iniScale.x,&iniScale.y, &iniScale.z };
                ImGui::InputFloat3("Scale", iniiniScaleArray[0]);

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
                            //事前準備
                            PreButtonInstantiate();
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
                } ImGui::SameLine();

                if (pSelectObj != nullptr)
                {
                    //セーブボタン
                    if (ImGui::Button("Save"))
                    {
                        //タイトルシーンだったら
                        switch (pSceneManager->GetNowSceneID())
                        {
                            //タイトルシーンだったら
                        case SCENE_ID::SCENE_ID_START:
                            
                            InstanceManager::SaveButton(JsonOperator::TITLE_BUTTON_JSON, sectionName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);

                        default:
                            break;
                        }
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

    //imguiでボタンを生成する前にやること
    void PreButtonInstantiate()
    {
        pCreateList.push_back(pSelectObj);
        SettingInfo setting{ selectLoadFileNameStr, sectionName ,iniPosition, iniRotate, iniScale };
        settingInfoList.push_back(setting);
        pSelectObj = nullptr;
    }

    //作ったオブジェクトの再移動等を出来るようにする
    void ReSetting()
    {
        //pCreateListの分だけ回す
        for (int i = 0; i < pCreateList.size(); i++)
        {
            ImGui::Begin(settingInfoList[i].sectionName.c_str());
            ImGui::End();
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
