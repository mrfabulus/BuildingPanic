#pragma once

#include "../SDL2_Interface.hpp"
#include "../Globals.hpp"
#include "SaveManager.hpp"
#include "../Scene/GameScene.hpp"
#include "../Scene/LogoScene.hpp"
#include "../Scene/MenuScene.hpp"

class GameManager
{
    // private:
    public:
        bool lastFrameStatus;
        GameScene* currentSceneObjectPtr;
        SaveManager* saveManager;
        uint16_t sceneState;
        int currentSceneID;
        short word14;
        short nextDemoplayStage;

    // public:
        GameManager()
        {
            this->currentSceneObjectPtr = nullptr;
            this->saveManager = nullptr;
            this->sceneState = 0;
            this->currentSceneID = 0;
            this->word14 = 0;
            this->nextDemoplayStage = 0;
            this->saveManager = new SaveManager();

            // Render an empty frame and flip it
            gSys.PerformEmptyBackSurfaceBlt();
            this->lastFrameStatus = gSys.Flip();
        }

        bool Update()
        {
            gSys.PerformEmptyBackSurfaceBlt();

            switch (this->sceneState)
            {
                case 0:
                    this->LoadNewScene();
                    break;
                case 1:
                    this->Tick();
                    break;
                case 2:
                    this->ChangeScene();
                    break;
                default:
                    return false;
            }
        }

        bool LoadNewScene()
        {
            GameScene* newScene = (GameScene*) nullptr;

            switch (this->currentSceneID)
            {
                case GameSceneID_Logo:
                    newScene = new LogoScene(this->saveManager);
                    break;
                case GameSceneID_Menu:
                    newScene = new MenuScene(this->saveManager);
                    break;
                case GameSceneID_Demoplay:
                    this->saveManager->CreatePlayerObjects();
                    this->saveManager->nextStage = this->nextDemoplayStage;
                    this->saveManager->nextLevel = 0;

                    if (this->nextDemoplayStage == 1)
                    {
                        this->saveManager->saveFlags = 0x1102;

                        // TODO: Check the original logic here..
                        
                        this->currentSceneID = GameSceneID_Ingame_Stage2;
                        this->nextDemoplayStage = 0;
                        newScene = nullptr; // new Ingame_Stage2_Scene();
                    }
                    else
                    {
                        this->saveManager->saveFlags = 0x1101;
                        
                        // TODO: Check the original logic here..

                        this->currentSceneID = GameSceneID_Ingame_Stage1;
                        newScene = nullptr; // new Ingame_Stage1_Scene();
                    }

                    break;
                case GameSceneID_CharacterChoice:
                    break;
                case GameSceneID_Scoreboard:
                    break;
                case GameSceneID_StageStatus:
                    break;
                case GameSceneID_AfterGameCredits:
                    break;
                case GameSceneID_Ingame_Stage1:
                    break;
                case GameSceneID_Ingame_Stage2:
                    break;
                case GameSceneID_Ingame_Stage3:
                    break;
                case GameSceneID_Ingame_Stage4:
                    break;
                case GameSceneID_Ingame_Stage5:
                    break;
            }

            this->currentSceneObjectPtr = newScene;

            if (!this->currentSceneObjectPtr || !this->currentSceneObjectPtr->init_OK)
            {
                // bpanic_ShowError_wrapper(8019, 1, memAllocFailStr);// If malloc failed or palette loading failed
                return false;
            }

            this->sceneState = 1;

            // this is a bit weird since there was no rendering for this frame but original code does this
            bool result = gSys.Flip();

            return result;
        }

        bool Tick()
        {
            InputProcessorBase* input = this->currentSceneObjectPtr->inputProcessor;
            
            if (input != nullptr)
                input->Process();

            this->currentSceneObjectPtr->Tick();

            if (this->currentSceneObjectPtr->finished)
                this->sceneState = 2;

            // Flip is logical here, it pushes out the freshly rendered frame
            bool result = gSys.Flip();
            return result;
        }

        bool ChangeScene()
        {
            int reference = this->currentSceneObjectPtr->GetNextSceneIDReference();
            int newSceneID = 0; // referenceToSceneID_Linker[reference];

            this->sceneState = 0;
            this->currentSceneID = newSceneID;
            
            if (this->currentSceneObjectPtr)
            {
                delete this->currentSceneObjectPtr;
                this->currentSceneObjectPtr = nullptr;
            }

            gSys.PerformEmptyBackSurfaceBlt();
            bool result = gSys.Flip();
            return result;
        }
};
