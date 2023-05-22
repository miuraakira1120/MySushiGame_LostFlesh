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

    int iniListButton;//�^�C�g���V�[���̃{�^���̔ԍ�

    //�g�p����ini�t�@�C���̖��O
    const std::string iniFileName = "UI.ini";

    // JSON�t�@�C���̖��O
    const std::string TITLE_JSON = "../Assets\\GameData\\TitleScene.json";

}

namespace Imgui_Obj
{
    //������
    void Initialize(SceneManager* pSceneManager_)
    {
        pText = new Text;
        pText->Initialize();
        pSceneManager = pSceneManager_;
        

        //�I�u�W�F�N�g��T���ē����
        FindAllObject();
    }

    //�X�V
    void Update()
    {
        pChangeSceneButton = (ChangeSceneButton*)pSceneManager->FindObject("ChangeSceneButton");

        //Imgui�𐶐�����
        InstantiateImgui();
        
    }

    //�J��
    void Release()
    {
        pText->Release();
    }

    //�I�u�W�F�N�g��T���ă|�C���^�ɓ����
    void FindAllObject()
    {
        /* pMaguro = (Maguro*)FindObject("Maguro");
         pSyari  = (Syari*)FindObject("Syari");*/
        

    }

    //Imgui�𐶐�����
    void InstantiateImgui()
    {
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
        //    //Imgui�X�^�[�g
        //    ImGui_ImplDX11_NewFrame();
        //    ImGui_ImplWin32_NewFrame();
        //    ImGui::NewFrame();

        //    //window���
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
////if (ImGui::Button("�I�u�W�F�N�g��ǉ�")) 
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
