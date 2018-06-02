#pragma once

#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"

class SaveManager;

struct Ingame_Stage3_Scene_Meta
{
    static const TileMeta StageBackgroundEntity_TileMeta;
};

class Ingame_Stage3_Scene : public Ingame_BasicStage_Scene
{
    public:
        Ingame_Stage3_Scene(SaveManager* aSaveManager);
        ~Ingame_Stage3_Scene();

        void LoadTileSets();
};
