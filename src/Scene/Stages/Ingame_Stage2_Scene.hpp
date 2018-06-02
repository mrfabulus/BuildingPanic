#pragma once

#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"

class SaveManager;

struct Ingame_Stage2_Scene_Meta
{
    static const TileMeta StageBackgroundEntity_TileMeta;
};

class Ingame_Stage2_Scene : public Ingame_BasicStage_Scene
{
    public:
        Ingame_Stage2_Scene(SaveManager* aSaveManager);
        ~Ingame_Stage2_Scene();

        void LoadTileSets();
};
