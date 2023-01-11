#include "Imgui_Obj.h"
#include "imgui/imgui.h"


//�R���X�g���N�^
Imgui_Obj::Imgui_Obj(GameObject* parent)
    :GameObject(parent, "Imgui_Obj"),pMaguro(nullptr),pSyari(nullptr)
{
}

//�f�X�g���N�^
Imgui_Obj::~Imgui_Obj()
{
}

//������
void Imgui_Obj::Initialize()
{
}

//�X�V
void Imgui_Obj::Update()
{
    //�I�u�W�F�N�g��T���ē����
    FindAllObject();

    //Imgui�𐶐�����
    InstantiateImgui();
    
}

//�`��
void Imgui_Obj::Draw()
{
}

//�J��
void Imgui_Obj::Release()
{
}

//�I�u�W�F�N�g��T��
void Imgui_Obj::FindAllObject()
{
    pMaguro = (Maguro*)FindObject("Maguro");
    pSyari  = (Syari*)FindObject("Syari");
}

//Imgui�𐶐�����
void Imgui_Obj::InstantiateImgui()
{
    //�V�����̃X�e�[�^�X��Imgui
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

    //�}�O���̃X�e�[�^�X��Imgui
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