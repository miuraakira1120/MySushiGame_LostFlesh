#include "Imgui_Obj.h"
#include "imgui/imgui.h"
#include "Time.h"
#include "Engine/IniOperator.h"

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

}

//初期化
void Imgui_Obj::Initialize(SceneManager* pSceneManager_)
{
    pText = new Text;
    pText->Initialize();
    pSceneManager = pSceneManager_;
}

//更新
void Imgui_Obj::Update()
{
    //オブジェクトを探して入れる
    FindAllObject();

    //Imguiを生成する
    InstantiateImgui();
}

//開放
void Imgui_Obj::Release()
{
    pText->Release();
}

//オブジェクトを探してポインタに入れる
void Imgui_Obj::FindAllObject()
{
   /* pMaguro = (Maguro*)FindObject("Maguro");
    pSyari  = (Syari*)FindObject("Syari");*/
    pChangeSceneButton = (ChangeSceneButton*)pSceneManager->FindObject("ChangeSceneButton");

}

//Imguiを生成する
void Imgui_Obj::InstantiateImgui()
{
    ImGui::Begin("Test Window");

    ImGui::Text("Hello, world %d", 123);

    //if (ImGui::Button("オブジェクトを追加")) 
    //{
    //    printf("Button\n");
    //}

    static char buf[256] = "";
    if (ImGui::InputText("string", buf, 256)) {
        printf("InputText\n");
    }

    static float f = 0.0f;
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    ImGui::End();


    ////////ボタンの位置////////////////
    ImGui::Begin("Botton Pos");
    ImGui::SliderFloat("ChangeSceneButtonX", &changeSceneButtonX, -1.0f, 1.0f);
    ImGui::SliderFloat("ChangeSceneButtonY", &changeSceneButtonY, -1.0f, 1.0f);
    pChangeSceneButton->SetPosition(changeSceneButtonX, changeSceneButtonY, 0);

    if (ImGui::Button("PositionSave"))
    {
        int iniListButton = IniOperator::AddList(iniFileName, "TitleButton");
        XMFLOAT3 changeSceneButtonPos = XMFLOAT3(changeSceneButtonX, changeSceneButtonY, 0);
        changeSceneButtonPos = Math::TransformToPixel(changeSceneButtonPos);
        IniOperator::SetValue(iniListButton, "ChangeSceneButtonX", changeSceneButtonX);
        IniOperator::SetValue(iniListButton, "ChangeSceneButtonY", changeSceneButtonY );
    }

    ImGui::End();
}