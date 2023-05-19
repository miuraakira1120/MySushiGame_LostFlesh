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

    //�^�C�g���V�[����������
    if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_START)
    {

        ///////////////////////�{�^���̈ʒu////////////////////////////////////////

        ImGui::Begin("Botton Pos");
        //////////////////////�X�^�[�g�{�^��/////////////////////////////////////////////////////

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

        //�}�E�X���[�h�Ȃ�V�����_�[�ňʒu���ς��Ȃ��ς��Ȃ�
        if (!pChangeSceneButton->GetMouseMode())
        {
            //�V�����_�[������܂ł͕ς��Ȃ�
            if (!changeSceneButtonX == 0 || !changeSceneButtonY == 0)
            {
                //�{�^���̈ʒu��ς���
                pChangeSceneButton->SetPosition(changeSceneButtonX, changeSceneButtonY, 0);
            }
        }
        else
        {
            //�}�E�X���[�h���{�^�����I�΂�ĂȂ������N���b�N��������Ă�����
            if (pChangeSceneButton->GetValue() && Input::IsMouseButton(1))
            {
                pChangeSceneButton->SetPosition(Math::PixelToTransform(Input::GetMousePosition()));
            }
        }

        //�{�^���̈ʒu�̃Z�[�u
        if (ImGui::Button("PositionSave"))
        {
            JsonOperator::AppendToJSONFileFloat(TITLE_JSON, "ChangeSceneButton", "posX", pChangeSceneButton->GetPosition().x);
            JsonOperator::AppendToJSONFileFloat(TITLE_JSON, "ChangeSceneButton", "posY", pChangeSceneButton->GetPosition().y);
        }

        ImGui::End();
        ///////////////////////////////////////////////////////////////////////////
    }
}

//TREENODE
//TreePop