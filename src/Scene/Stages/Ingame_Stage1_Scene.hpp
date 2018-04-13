#pragma once

#include "Ingame_BasicStage_Scene.hpp"

class SaveManager;

struct Ingame_Stage1_Scene_Meta
{
    static const TileMeta StageBackgroundEntity_TileMeta;
};

class Ingame_Stage1_Scene : public Ingame_BasicStage_Scene
{
    public:
        Ingame_Stage1_Scene(SaveManager* aSaveManager);
        ~Ingame_Stage1_Scene();

        void LoadTileSets();
};
