#pragma once

#include "../SDL2_Interface.hpp"
#include "../Globals.hpp"

class GameScene;
class SaveManager;

class GameManager
{
    // private:
    public:
        GameScene* currentSceneObjectPtr;
        SaveManager* saveManager;
        uint16_t sceneState;
        int currentSceneID;
        short word14;
        short nextDemoplayStage;

    // public:
        GameManager();

        bool Update();

        bool LoadNewScene();

        bool Tick();

        bool ChangeScene();
};
