#include "Imgui_Obj.h"
#include "imgui/imgui.h"


//コンストラクタ
Imgui_Obj::Imgui_Obj(GameObject* parent)
    :GameObject(parent, "Imgui_Obj"),pMaguro(nullptr),pSyari(nullptr)
{
}

//デストラクタ
Imgui_Obj::~Imgui_Obj()
{
}

//初期化
void Imgui_Obj::Initialize()
{
}

//更新
void Imgui_Obj::Update()
{
    //オブジェクトを探して入れる
    FindAllObject();

    //Imguiを生成する
    InstantiateImgui();
    
}

//描画
void Imgui_Obj::Draw()
{
}

//開放
void Imgui_Obj::Release()
{
}

//オブジェクトを探す
void Imgui_Obj::FindAllObject()
{
    pMaguro = (Maguro*)FindObject("Maguro");
    pSyari  = (Syari*)FindObject("Syari");
}

//Imguiを生成する
void Imgui_Obj::InstantiateImgui()
{
    //シャリのステータスのImgui
    ImGui::Begin("Syari State");
    if (pSyari != nullptr)
    {
        ImGui::Text("SyariPositionX  ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(pSyari->GetPosition().x).c_str());

        ImGui::Text("SyariPositionY  ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(pSyari->GetPosition().y).c_str());

        ImGui::Text("SyariPositionZ  ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(pSyari->GetPosition().z).c_str());
    }
    ImGui::End();

    //マグロのステータスのImgui
    ImGui::Begin("Maguro State");
    if (pMaguro != nullptr)
    {
        ImGui::Text("MaguroPositionX  ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(pMaguro->GetPosition().x).c_str());

        ImGui::Text("MaguroPositionY  ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(pMaguro->GetPosition().y).c_str());

        ImGui::Text("MaguroPositionZ  ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(pMaguro->GetPosition().z).c_str());
    }
    ImGui::End();
}

/* static int clickCount;*/
    /*if (ImGui::Button("click"))
    {
        clickCount += 1;
    }
    ImGui::SameLine();
    std::string c = "ClickCount " + std::to_string(clickCount);
    */