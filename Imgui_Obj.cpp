#include "Imgui_Obj.h"
#include "imgui/imgui.h"
#include "Time.h"
#include "Engine/JsonOperator.h"

namespace
{
    Text* pText;
    int gameTimerID;
    ChangeSceneButton* pChangeSceneButton;
    SceneManager* pSceneManager;

    float changeSceneButtonX;
    float changeSceneButtonY;

    int iniListButton;//�^�C�g���V�[���̃{�^���̔ԍ�

    //�g�p����ini�t�@�C���̖��O
    const std::string iniFileName = "UI.ini";

    // JSON�t�@�C���̖��O
    const std::string TITLE_JSON = "../Assets\\GameData\\TitleScene.json";

}

//������
void Imgui_Obj::Initialize(SceneManager* pSceneManager_)
{
    pText = new Text;
    pText->Initialize();
    pSceneManager = pSceneManager_;
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


    ////////�{�^���̈ʒu/////////////////////////////
    
    ImGui::Begin("Botton Pos");
    //�X�^�[�g�{�^��
    ImGui::SliderFloat("ChangeSceneButtonX", &changeSceneButtonX, -1.0f, 1.0f);
    ImGui::SliderFloat("ChangeSceneButtonY", &changeSceneButtonY, -1.0f, 1.0f);
    if (!changeSceneButtonX == 0 || !changeSceneButtonY == 0)
    {
        pChangeSceneButton->SetPosition(changeSceneButtonX, changeSceneButtonY, 0);
    }

    if (ImGui::Button("PositionSave"))
    {
        JsonOperator::AppendToJSONFileFloat(TITLE_JSON, "ChangeSceneButton", "posX", changeSceneButtonX);
        JsonOperator::AppendToJSONFileFloat(TITLE_JSON, "ChangeSceneButton", "posY", changeSceneButtonY);
    }

    ImGui::End();
}