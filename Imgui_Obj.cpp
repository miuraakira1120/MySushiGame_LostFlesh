#include "Imgui_Obj.h"
#include "imgui/imgui.h"
#include "Time.h"

//コンストラクタ
Imgui_Obj::Imgui_Obj(GameObject* parent)
    :GameObject(parent, "Imgui_Obj"),pMaguro(nullptr),pSyari(nullptr), pText(nullptr)
{
}

//デストラクタ
Imgui_Obj::~Imgui_Obj()
{
}

//初期化
void Imgui_Obj::Initialize()
{
    pText = new Text;
    pText->Initialize();
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
    //pText->Draw(500, 75, "Hello");
}

//開放
void Imgui_Obj::Release()
{
    pText->Release();
}

//オブジェクトを探してポインタに入れる
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

    ImGui::Begin("Time");
    ImGui::Text("Timer ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(Time::GetTimef()).c_str());
    ImGui::SameLine();
    ImGui::Text("s");
    ImGui::End();

    ImGui::Begin("accel");
    ImGui::Text("accel ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->accel).c_str());
    ImGui::SameLine();
    ImGui::Text("s");

    ImGui::Text("kadoX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].x).c_str());
    ImGui::Text("kadoY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].y).c_str());
    ImGui::Text("kadoZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].z).c_str());

    ImGui::Text("kadoX2 ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].x).c_str());
    ImGui::Text("kadoY2 ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].y).c_str());
    ImGui::Text("kadoZ2 ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].z).c_str());
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