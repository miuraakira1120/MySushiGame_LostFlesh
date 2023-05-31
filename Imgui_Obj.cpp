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

    //char�^�̔z��̃T�C�Y(2��8��)
    const int CHAR_SIZE = 256;

    //�e�����ɂ��邩
    int parentNum;

    int buttonKinds = static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);//�{�^���̎��

    IniType iniType = IniType::NONE;

    int nextScene;//���ɍs���V�[��
    int SceneChangeNextScene; //SceneChange�̎��Ɏg�����ɍs���V�[��

    std::string selectUniqueName;//�I�𒆂̃I�u�W�F�N�g�̃��j�[�N�Ȗ��O
    
    GameObject* pSelectObj;//�I�𒆂̃I�u�W�F�N�g
    std::string selectButtonKinds;//�I�𒆂̃I�u�W�F�N�g�̎��
    string selectLoadFileNameStr;//�I�𒆂̃I�u�W�F�N�g���ǂݍ��މ摜�⃂�f���̃t�@�C����

    char loadFileName[CHAR_SIZE] = "";//�ǂݍ��ރt�@�C����
    char sectionName[CHAR_SIZE];//�Z�N�V�����̖��O 
    XMFLOAT3 iniPosition = { 0,0,0 };//�ʒu
    XMFLOAT3 iniScale = { 1,1,1 };//�g�嗦
    XMFLOAT3 iniRotate = { 0,0,0 };//����
    std::string selectWriteFile;//�I�𒆂̃I�u�W�F�N�g���ۑ�������ۂɏ�������JSON�̃t�@�C����

    //�Đݒ�̎��ɕK�v�ȏ��
    struct SettingInfo
    {
        SettingInfo(GameObject* obj, std::string loadFileName, std::string sectionName, std::string writeFileName, XMFLOAT3 position, XMFLOAT3 scale, XMFLOAT3 rotate) :
            pObject{ obj },loadFileName { loadFileName }, sectionName{ sectionName }, writeFile{ writeFileName }, iniPosition
            {position}, iniRotate{ rotate }, iniScale{ scale } {}

        GameObject* pObject;
        std::string loadFileName = "";//�ǂݍ��ރt�@�C����
        std::string sectionName;//�Z�N�V�����̖��O 
        std::string writeFile;//�ۑ�������ۂɏ�������JSON�̃t�@�C����
        XMFLOAT3 iniPosition;//�ʒu
        XMFLOAT3 iniRotate;//����
        XMFLOAT3 iniScale;//�g�嗦

    };

    std::vector<SettingInfo> settingInfoList;//������{�^���̃��X�g 
    
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
        //�쐬�p��Imgui���o��
        ImguiIniObj();

        //������I�u�W�F�N�g�̍Đݒ���o����悤�ɂ���
        ReSettingButton();

        //�y�ɃV�[���`�F���W�o����悤�ɂ���
        SceneChangeImgui();

        //�^�C�g���V�[����������
        if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_START)
        {
            ///////////////////////�{�^���̈ʒu////////////////////////////////////////

            ImGui::Begin("Botton Pos");
            //////////////////////�X�^�[�g�{�^��/////////////////////////////////////////////////////

            static float testFloat;
            ImGui::InputFloat("x", &testFloat, -1, 1);

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

                //�Z�N�V������
                ImGui::Text("ObjectName");
                ImGui::InputText("name", sectionName, CHAR_SIZE);
                selectUniqueName = sectionName;

                //�ǂݍ��ރt�@�C���������
                ImGui::Text("LoadFileName");
                ImGui::InputText(".png", loadFileName, CHAR_SIZE);

                //Transfom�̏������
                ImGui::Text("Transform");

                //�ʒu
                float speed = 0.05f;
                //�Q�ƂŐ���
                float* iniPositionArray[3] = { &iniPosition.x, &iniPosition.y, &iniPosition.z };
                ImGui::DragFloat3("Position", iniPositionArray[0], speed, -1.0f, 1.0f);

                //����
                float* iniRotateArray[3] = { &iniRotate.x,&iniRotate.y, &iniRotate.z };
                ImGui::DragFloat3("Rotate", iniRotateArray[0], speed, -1.0f, 1.0f);

                //�g�嗦
                float* iniScaleArray[3] = { &iniScale.x,&iniScale.y, &iniScale.z };
                ImGui::DragFloat3("Scale", iniScaleArray[0], speed, -1.0f, 1.0f);

                //�ǂ�Ȏ�ނ̃{�^���𐶐����邩
                ImGui::Text("ButtonType");
                //ImGui::RadioButton("SceneChange", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON)); ImGui::SameLine();
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
                        selectButtonKinds = JsonOperator::ButtonToString(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);

                        //�g���q��png��ǉ�
                        selectLoadFileNameStr = loadFileName;
                        selectLoadFileNameStr += ".png";

                        //�ۑ����Ă��Ȃ��I�u�W�F�N�g�͏���
                        if (pSelectObj != nullptr)
                        {
                            pSelectObj->KillMe();
                        }

                        //�e�����̃V�[���Ȃ�
                        if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                        {    
                            //����
                            pSelectObj = InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
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
                } 

                if (pSelectObj != nullptr)
                {
                    ImGui::SameLine();
                    //�Z�[�u�{�^��
                    if (ImGui::Button("Save"))
                    {
                        //�^�C�g���V�[����������
                        switch (pSceneManager->GetNowSceneID())
                        {
                            //�^�C�g���V�[����������
                        case SCENE_ID::SCENE_ID_START:
                            InstanceManager::SaveButton(JsonOperator::TITLE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                            break;
                        default:
                            break;
                        }
                        //����
                        RearButtonInstantiate();

                    }ImGui::SameLine();

                    //�폜�{�^��
                    if (ImGui::Button("Delete"))
                    {
                        pSelectObj->KillMe();
                        pSelectObj = nullptr;
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

    //imgui�Ń{�^����ۑ�������ɂ�邱��
    void RearButtonInstantiate()
    {
        SettingInfo setting{ pSelectObj, selectLoadFileNameStr, selectUniqueName , selectWriteFile,iniPosition, iniRotate, iniScale };
        settingInfoList.push_back(setting);
        pSelectObj = nullptr;
    }

    //������{�^���̍Ĉړ������o����悤�ɂ���
    void ReSettingButton()
    {
        //�{�^��
        {
            //pCreateList�̕�������
            for (int i = 0; i < settingInfoList.size(); i++)
            {
                ImGui::Begin(settingInfoList[i].sectionName.c_str());

                //�ǂݍ��ރt�@�C���������
                ImGui::Text("LoadFileName");
                char sec[CHAR_SIZE];
                settingInfoList[i].loadFileName.copy(sec, CHAR_SIZE - 1);
                sec[settingInfoList[i].loadFileName.length()] = '\0';
                ImGui::InputText("LoadFile", sec, CHAR_SIZE);
                settingInfoList[i].loadFileName = sec;
                if (ImGui::Button("Decision"))
                {
                    settingInfoList[i].pObject->SetPathName(loadFileName);
                }

                //Transfom�̏������
                ImGui::Text("Transform");
                float speed = 0.05f;
                //�ʒu
                float* iniPositionArrayTmp[3] = { &settingInfoList[i].iniPosition.x, &settingInfoList[i].iniPosition.y, &settingInfoList[i].iniPosition.z };
                ImGui::DragFloat3("Position", iniPositionArrayTmp[0], speed, -1.0f, 1.0f);
                settingInfoList[i].pObject->SetPosition(settingInfoList[i].iniPosition);

                //����
                float* iniRotateArrayTmp[3] = { &settingInfoList[i].iniRotate.x,&settingInfoList[i].iniRotate.y, &settingInfoList[i].iniRotate.z };
                ImGui::DragFloat3("Rotate", iniRotateArrayTmp[0], speed, -1.0f, 1.0f);
                settingInfoList[i].pObject->SetRotate(settingInfoList[i].iniRotate);

                //�g�嗦
                float* iniScaleArrayTmp[3] = { &settingInfoList[i].iniScale.x,&settingInfoList[i].iniScale.y, &settingInfoList[i].iniScale.z };
                ImGui::DragFloat3("Scale", iniScaleArrayTmp[0], speed, -1.0f, 1.0f);
                settingInfoList[i].pObject->SetScale(settingInfoList[i].iniScale);

                //�ۑ�
                if (ImGui::Button("Save"))
                {
                    InstanceManager::OverwriteSaveButton(
                        settingInfoList[i].writeFile,
                        settingInfoList[i].sectionName,
                        settingInfoList[i].loadFileName, 
                        settingInfoList[i].iniPosition, 
                        settingInfoList[i].iniRotate, 
                        settingInfoList[i].iniScale);
                }
                //�폜
                if (ImGui::Button("Delete"))
                {
                    settingInfoList[i].pObject->KillMe();

                }

                ImGui::End();
            }
        }
        //�I�u�W�F�N�g
        {

        }
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
