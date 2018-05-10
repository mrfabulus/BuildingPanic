#pragma once

#include "Globals.hpp"
#include "SDL2_Interface.hpp"

class GameScene;
class SaveManager;

class GameManager
{
    public:
        GameScene* currentSceneObjectPtr;
        SaveManager* saveManager;
        uint16_t sceneState;
        int currentSceneID;
        short word14;
        short nextDemoplayStage;

        GameManager();
        virtual ~GameManager();

        bool Update();
        bool LoadNewScene();
        bool Tick();
        bool ChangeScene();
};
