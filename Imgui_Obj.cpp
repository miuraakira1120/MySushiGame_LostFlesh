#include "Imgui_Obj.h"
#include "imgui/imgui.h"
#include "Time.h"


//�R���X�g���N�^
Imgui_Obj::Imgui_Obj(GameObject* parent)
    :GameObject(parent, "Imgui_Obj"),pMaguro(nullptr),pSyari(nullptr), pText(nullptr)
{
}

//�f�X�g���N�^
Imgui_Obj::~Imgui_Obj()
{
}

//������
void Imgui_Obj::Initialize()
{
    pText = new Text;
    pText->Initialize();
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
    //pText->Draw(500, 75, "Hello");
    
}

//�J��
void Imgui_Obj::Release()
{
    pText->Release();
}

//�I�u�W�F�N�g��T���ă|�C���^�ɓ����
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

    ImGui::Text("UP_RIGHT_FRONTX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].x).c_str());
    ImGui::Text("UP_RIGHT_FRONTY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].y).c_str());
    ImGui::Text("UP_RIGHT_FRONTZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].z).c_str());
    ImGui::NewLine();

    ImGui::Text("UP_RIGHT_BACKX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].x).c_str());
    ImGui::Text("UP_RIGHT_BACKY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].y).c_str());
    ImGui::Text("UP_RIGHT_BACKZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].z).c_str());
    ImGui::NewLine();

    ImGui::Text("UP_LEFT_FRONTX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_FRONT].x).c_str());
    ImGui::Text("UP_LEFT_FRONTY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_FRONT].y).c_str());
    ImGui::Text("UP_LEFT_FRONTZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_FRONT].z).c_str());
    ImGui::NewLine();

    ImGui::Text("UP_LEFT_BACKX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_BACK].x).c_str());
    ImGui::Text("UP_LEFT_BACKY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_BACK].y).c_str());
    ImGui::Text("UP_LEFT_BACKZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_BACK].z).c_str());
    ImGui::NewLine();

    ImGui::Text("DOWN_RIGHT_FRONTX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_FRONT].x).c_str());
    ImGui::Text("DOWN_RIGHT_FRONTY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_FRONT].y).c_str());
    ImGui::Text("DOWN_RIGHT_FRONTZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_FRONT].z).c_str());
    ImGui::NewLine();

    ImGui::Text("DOWN_RIGHT_BACKX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_BACK].x).c_str());
    ImGui::Text("DOWN_RIGHT_BACKY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_BACK].y).c_str());
    ImGui::Text("DOWN_RIGHT_BACKZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_BACK].z).c_str());
    ImGui::NewLine();

    ImGui::Text("DOWN_LEFT_FRONTX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_FRONT].x).c_str());
    ImGui::Text("DOWN_LEFT_FRONTY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_FRONT].y).c_str());
    ImGui::Text("DOWN_LEFT_FRONTZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_FRONT].z).c_str());
    ImGui::NewLine();

    ImGui::Text("DOWN_LEFT_BACKX ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_BACK].x).c_str());
    ImGui::Text("DOWN_LEFT_BACKY ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_BACK].y).c_str());
    ImGui::Text("DOWN_LEFT_BACKZ ");
    ImGui::SameLine();
    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_BACK].z).c_str());
    ImGui::NewLine();

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