#include "Imgui_Obj.h"
#include "imgui/imgui.h"
#include "Time.h"
#include "Engine/JsonOperator.h"

#include "Engine/GameObject.h"
#include "Maguro.h"
#include "Syari.h"
#include "Engine/Text.h"
#include "ChangeSceneButton.h"
#include "PlayerControlButton.h"
#include "Engine/SceneManager.h"
#include "Engine/Math.h"
#include "Engine/Input.h"

#include "Pause.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "GameManager.h"

//���̃N���X���쐬���邩
enum class IniType
{
    NONE,
    BUTTON,
    ENEMY,
    TYPE_MAX

};

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

    //�e�����ɂ��邩
    int parentNum;

    int buttonKinds;//�{�^���̎��

    IniType iniType = IniType::NONE;

    char loadFileName[256] = "";//�ǂݍ��ރt�@�C����

    XMFLOAT3 iniPosition = { 0,0,0 };//�ʒu
    XMFLOAT3 iniScale = { 1,1,1 };//�g�嗦
    XMFLOAT3 iniRotate = { 0,0,0 };//����

    int nextScene;//���ɍs���V�[��
    int SceneChangeNextScene; //SceneChange�̎��Ɏg�����ɍs���V�[��
}

namespace Imgui_Obj
{
    //������
    void Initialize(SceneManager* pSceneManager_)
    {
        pText = new Text;
        pText->Initialize();
        pSceneManager = pSceneManager_;
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

    //Imgui�𐶐�����
    void InstantiateImgui()
    {
        //�|�[�Y����������
        if (GameManager::GetIsPause())
        {
            ImguiIniObj();
        }

        SceneChangeImgui();

        //�^�C�g���V�[����������
        if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_START)
        {
            ///////////////////////�{�^���̈ʒu////////////////////////////////////////

            ImGui::Begin("Botton Pos");
            //////////////////////�X�^�[�g�{�^��/////////////////////////////////////////////////////


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
                JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posX", pChangeSceneButton->GetPosition().x);
                JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posY", pChangeSceneButton->GetPosition().y);
            }

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

    //�I�u�W�F�N�g�𐶐�����Imgui���o���֐�
    void ImguiIniObj()
    {
        //Pause Setting��Imgui���쐬
        ImGui::Begin("Pause Setting");
        if (ImGui::TreeNode("Instantiate"))
        {
            if (ImGui::Button("Button"))
            {
                iniType = IniType::BUTTON;
            }
            if (ImGui::Button("Enemy"))
            {
                iniType = IniType::ENEMY;
            }
            ImGui::TreePop();

            //�{�^���쐬���[�h�Ȃ�
            if (iniType == IniType::BUTTON)
            {
                ImGui::Begin("Button Instantiate");

                //�ǂݍ��ރt�@�C���������
                ImGui::Text("LoadFileName");
                ImGui::InputText(".png", loadFileName, 256);               

                //Transfom�̏������
                ImGui::Text("Transform");

                //�ʒu
                //�Q�ƂŐ���
                float* iniPositionArray[3] = { &iniPosition.x, &iniPosition.y, &iniPosition.z };
                ImGui::InputFloat3("Position", iniPositionArray[0]);

                //����
                float* iniRotateArray[3] = { &iniRotate.x,&iniRotate.y, &iniRotate.z };
                ImGui::InputFloat3("Rotate", iniRotateArray[0]);

                //�g�嗦
                float* iniiniScaleArray[3] = { &iniScale.x,&iniScale.y, &iniScale.z };
                ImGui::InputFloat3("Scale", iniiniScaleArray[0]);

                //�ǂ�ȃ{�^���𐶐����邩
                ImGui::Text("ButtonType");

                //�ǂ�Ȏ�ނ̃{�^���𐶐����邩
                ImGui::RadioButton("SceneChange", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON)); ImGui::SameLine();
                ImGui::RadioButton("PlayerControl", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON)); 

                //�V�[���`�F���W�{�^�����쐬����\��Ȃ�
                if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON))
                {
                    ImGui::Text("NextScene");
                    ImGui::RadioButton("Title", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
                    ImGui::RadioButton("Play", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
                    ImGui::RadioButton("GameOver", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER)); ImGui::SameLine();
                    ImGui::RadioButton("Clear", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL));
                }

                //�e�I�u�W�F�N�g�͉���(�ǂ��Ő������邩)
                ImGui::Text("Parent");
                ImGui::RadioButton("NowScene", &parentNum, static_cast<int>(GameManager::ParentNum::NOW_SCENE)); ImGui::SameLine();
                ImGui::RadioButton("Pause", &parentNum, static_cast<int>(GameManager::ParentNum::PAUSE));               

                //�����{�^��
                if (ImGui::Button("Instantiate"))
                {

                    //�V�[���`�F���W�{�^�����쐬����Ȃ�
                    if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON))
                    {

                    }

                    //�v���C���[�̃{�^���z�u��ς���{�^�����쐬����Ȃ�
                    if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON))
                    {
                        //�g���q��png��ǉ�
                        string loadFileNameStr = loadFileName;
                        loadFileNameStr += ".png";

                        //�e�����̃V�[���Ȃ�
                        if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                        {
                           
                            InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), loadFileNameStr, iniPosition, iniRotate, iniScale);
            
                        }

                        //�e���|�[�Y�Ȃ�
                        if (parentNum == static_cast<int>(GameManager::ParentNum::PAUSE))
                        {

                        }

                        //�e���v���C���[�Ȃ�
                        if (parentNum == static_cast<int>(GameManager::ParentNum::PLAYER))
                        {

                        }
                       
                    }
                } ImGui::SameLine();

                //�Z�[�u�{�^��
                if (ImGui::Button("Save"))
                {
                    //�^�C�g���V�[����������
                    switch (pSceneManager->GetNowSceneID())
                    {
                        //�^�C�g���V�[����������
                    case SCENE_ID::SCENE_ID_START:
                        JsonOperator::AppendToJSONFileString(JsonOperator::TITLE_JSON, );
                    default:
                        break;
                    }
                }


                //�L�����Z���{�^��
                if (ImGui::Button("Cancel"))
                {

                    iniType = IniType::NONE;
                }
                ImGui::End();

            }
        }
        ImGui::End();
    }

    //�V�[���`�F���W����Imgui�𐶐�����֐�
    void SceneChangeImgui()
    {
        ImGui::Begin("Scene Change");
        ImGui::RadioButton("Title", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
        ImGui::RadioButton("Play", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
        ImGui::RadioButton("Goal", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL)); ImGui::SameLine();
        ImGui::RadioButton("GameOver", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER));

        if (ImGui::Button("Scene Change"))
        {
            pSceneManager->ChangeScene(static_cast<SCENE_ID>(nextScene));
        }
        ImGui::End();
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
