#pragma once

#include "Ingame_BasicStage_Scene.hpp"

class SaveManager;

class Ingame_Stage1_Scene : public Ingame_BasicStage_Scene
{
    public:
        Ingame_Stage1_Scene(SaveManager* aSaveManager);
        ~Ingame_Stage1_Scene();

        void LoadTileSets();
};
