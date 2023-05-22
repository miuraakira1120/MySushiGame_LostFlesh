#include "Imgui_Obj.h"
#include "imgui/imgui.h"
#include "Time.h"
#include "Engine/JsonOperator.h"

#include "Engine/GameObject.h"
#include "Maguro.h"
#include "Syari.h"
#include "Engine/Text.h"
#include "ChangeSceneButton.h"
#include "Engine/SceneManager.h"
#include "Engine/Math.h"
#include "Engine/Input.h"

#include "Pause.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "GameManager.h"

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

    // JSONファイルの名前
    const std::string TITLE_JSON = "../Assets\\GameData\\TitleScene.json";

}

namespace Imgui_Obj
{
    //初期化
    void Initialize(SceneManager* pSceneManager_)
    {
        pText = new Text;
        pText->Initialize();
        pSceneManager = pSceneManager_;
        

        //オブジェクトを探して入れる
        FindAllObject();
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

    //オブジェクトを探してポインタに入れる
    void FindAllObject()
    {
        /* pMaguro = (Maguro*)FindObject("Maguro");
         pSyari  = (Syari*)FindObject("Syari");*/
        

    }

    //Imguiを生成する
    void InstantiateImgui()
    {
        //タイトルシーンだったら
        if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_START)
        {

            ///////////////////////ボタンの位置////////////////////////////////////////

            ImGui::Begin("Botton Pos");
            //////////////////////スタートボタン/////////////////////////////////////////////////////

            /*int MouseMode = false;
            ImGui::RadioButton("MouseModeON", &MouseMode, TRUE);
            ImGui::SameLine();
            ImGui::RadioButton("MouseMode", &MouseMode, FALSE);*/


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
                JsonOperator::AppendToJSONFileFloat(TITLE_JSON, "ChangeSceneButton", "posX", pChangeSceneButton->GetPosition().x);
                JsonOperator::AppendToJSONFileFloat(TITLE_JSON, "ChangeSceneButton", "posY", pChangeSceneButton->GetPosition().y);
            }

            ImGui::End();
            ///////////////////////////////////////////////////////////////////////////

            ImGui::Begin("BlackBack Pos");


            ImGui::SliderFloat("ChangeSceneButtonX", &changeSceneButtonX, -1.0f, 1.0f);
            ImGui::SliderFloat("ChangeSceneButtonY", &changeSceneButtonY, -1.0f, 1.0f);

            GameManager::SetPausePos((XMFLOAT3)(changeSceneButtonX, changeSceneButtonY, 0));

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
