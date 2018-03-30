#pragma once

#include "../SDL2_Interface.hpp"
#include "../Globals.hpp"
#include "SaveManager.hpp"
#include "../Scene/GameScene.hpp"
#include "../Scene/LogoScene.hpp"

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
                    break;
                case GameSceneID_Demoplay:
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

        }

        bool ChangeScene()
        {

        }
};
