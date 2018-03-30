#pragma once

#include "SDL2_Interface.hpp"
#include "Globals.hpp"
#include "SaveManager.hpp"

class GameManager
{
    // private:
    public:
        bool lastFrameStatus;
        void* currentSceneObjectPtr;
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

        }

        bool Tick()
        {

        }

        bool ChangeScene()
        {

        }
};
