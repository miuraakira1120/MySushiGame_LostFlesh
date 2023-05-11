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

    float ChangeSceneButtonX;
    float ChangeSceneButtonY;

    int iniListButton;//�^�C�g���V�[���̃{�^���̔ԍ�

    //�g�p����ini�t�@�C���̖��O
    const std::string iniFileName = "UI.ini";

}

//������
void Imgui_Obj::Initialize(SceneManager* pSceneManager_)
{
    pText = new Text;
    pText->Initialize();
    pSceneManager = pSceneManager_;
    InstantiateImgui();
}

//�X�V
void Imgui_Obj::Update()
{
    //�I�u�W�F�N�g��T���ē����
    FindAllObject();

    //Imgui�𐶐�����
    InstantiateImgui();
}

//�J��
void Imgui_Obj::Release()
{
    pText->Release();
}

//�I�u�W�F�N�g��T���ă|�C���^�ɓ����
void Imgui_Obj::FindAllObject()
{
   /* pMaguro = (Maguro*)FindObject("Maguro");
    pSyari  = (Syari*)FindObject("Syari");*/
    pChangeSceneButton = (ChangeSceneButton*)pSceneManager->FindObject("ChangeSceneButton");

}

//Imgui�𐶐�����
void Imgui_Obj::InstantiateImgui()
{
    ImGui::Begin("Test Window");

    ImGui::Text("Hello, world %d", 123);

    //if (ImGui::Button("�I�u�W�F�N�g��ǉ�")) 
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


    ////////�{�^���̈ʒu////////////////
    ImGui::Begin("Botton Pos");
    ImGui::SliderFloat("ChangeSceneButtonX", &ChangeSceneButtonX, -1.0f, 1.0f);
    ImGui::SliderFloat("ChangeSceneButtonY", &ChangeSceneButtonY, -1.0f, 1.0f);

    if (ImGui::Button("PositionSave")) 
    {
        int iniListButton = IniOperator::AddList(iniFileName, "TitleButton");
        IniOperator::SetValue(iniListButton, "ChangeSceneButtonX", ChangeSceneButtonX);
        IniOperator::SetValue(iniListButton, "ChangeSceneButtonY", ChangeSceneButtonY);
    }

    ImGui::End();

    //if (pSyari != nullptr)
    //{
    //    //�V�����̃X�e�[�^�X��Imgui
    //    ImGui::Begin("Syari State");
    //    if (pSyari != nullptr)
    //    {
    //        ImGui::Text("SyariPositionX  ");
    //        ImGui::SameLine();
    //        ImGui::Text(std::to_string(pSyari->GetPosition().x).c_str());

    //        ImGui::Text("SyariPositionY  ");
    //        ImGui::SameLine();
    //        ImGui::Text(std::to_string(pSyari->GetPosition().y).c_str());

    //        ImGui::Text("SyariPositionZ  ");
    //        ImGui::SameLine();
    //        ImGui::Text(std::to_string(pSyari->GetPosition().z).c_str());

    //    }
    //    ImGui::End();

    //    //�}�O���̃X�e�[�^�X��Imgui
    //    ImGui::Begin("Maguro State");
    //    if (pMaguro != nullptr)
    //    {
    //        ImGui::Text("MaguroPositionX  ");
    //        ImGui::SameLine();
    //        ImGui::Text(std::to_string(pMaguro->GetPosition().x).c_str());

    //        ImGui::Text("MaguroPositionY  ");
    //        ImGui::SameLine();
    //        ImGui::Text(std::to_string(pMaguro->GetPosition().y).c_str());

    //        ImGui::Text("MaguroPositionZ  ");
    //        ImGui::SameLine();
    //        ImGui::Text(std::to_string(pMaguro->GetPosition().z).c_str());
    //    }
    //    ImGui::End();

    //    gameTimerID = Time::GetTimerID();
    //    ImGui::Begin("Time");
    //    ImGui::Text("Timer ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(Time::GetTimef(gameTimerID)).c_str());
    //    ImGui::SameLine();
    //    ImGui::Text("s");
    //    ImGui::End();

    //    ImGui::Begin("accel");
    //    ImGui::Text("accel ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->accel).c_str());
    //    ImGui::SameLine();
    //    ImGui::Text("s");

    //    ImGui::Text("UP_RIGHT_FRONTX ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].x).c_str());
    //    ImGui::Text("UP_RIGHT_FRONTY ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].y).c_str());
    //    ImGui::Text("UP_RIGHT_FRONTZ ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_FRONT].z).c_str());
    //    ImGui::NewLine();

    //    ImGui::Text("UP_RIGHT_BACKX ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].x).c_str());
    //    ImGui::Text("UP_RIGHT_BACKY ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].y).c_str());
    //    ImGui::Text("UP_RIGHT_BACKZ ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_RIGHT_BACK].z).c_str());
    //    ImGui::NewLine();

    //    ImGui::Text("UP_LEFT_FRONTX ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_FRONT].x).c_str());
    //    ImGui::Text("UP_LEFT_FRONTY ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_FRONT].y).c_str());
    //    ImGui::Text("UP_LEFT_FRONTZ ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_FRONT].z).c_str());
    //    ImGui::NewLine();

    //    ImGui::Text("UP_LEFT_BACKX ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_BACK].x).c_str());
    //    ImGui::Text("UP_LEFT_BACKY ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_BACK].y).c_str());
    //    ImGui::Text("UP_LEFT_BACKZ ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[UP_LEFT_BACK].z).c_str());
    //    ImGui::NewLine();

    //    ImGui::Text("DOWN_RIGHT_FRONTX ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_FRONT].x).c_str());
    //    ImGui::Text("DOWN_RIGHT_FRONTY ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_FRONT].y).c_str());
    //    ImGui::Text("DOWN_RIGHT_FRONTZ ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_FRONT].z).c_str());
    //    ImGui::NewLine();

    //    ImGui::Text("DOWN_RIGHT_BACKX ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_BACK].x).c_str());
    //    ImGui::Text("DOWN_RIGHT_BACKY ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_BACK].y).c_str());
    //    ImGui::Text("DOWN_RIGHT_BACKZ ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_RIGHT_BACK].z).c_str());
    //    ImGui::NewLine();

    //    ImGui::Text("DOWN_LEFT_FRONTX ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_FRONT].x).c_str());
    //    ImGui::Text("DOWN_LEFT_FRONTY ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_FRONT].y).c_str());
    //    ImGui::Text("DOWN_LEFT_FRONTZ ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_FRONT].z).c_str());
    //    ImGui::NewLine();

    //    ImGui::Text("DOWN_LEFT_BACKX ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_BACK].x).c_str());
    //    ImGui::Text("DOWN_LEFT_BACKY ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_BACK].y).c_str());
    //    ImGui::Text("DOWN_LEFT_BACKZ ");
    //    ImGui::SameLine();
    //    ImGui::Text(std::to_string(pSyari->vertexBonePos[DOWN_LEFT_BACK].z).c_str());
    //    ImGui::NewLine();

    //    ImGui::End();
    //}
    //
}


/* static int clickCount;*/
    /*if (ImGui::Button("click"))
    {
        clickCount += 1;
    }
    ImGui::SameLine();
    std::string c = "ClickCount " + std::to_string(clickCount);
    */