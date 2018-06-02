#pragma once

#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"

class SaveManager;

struct Ingame_Stage5_Scene_Meta
{
    static const TileMeta StageBackgroundEntity_TileMeta;
};

class Ingame_Stage5_Scene : public Ingame_BasicStage_Scene
{
    public:
        Ingame_Stage5_Scene(SaveManager* aSaveManager);
        ~Ingame_Stage5_Scene();

        void LoadTileSets();
};
