#pragma once

#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"

class SaveManager;

struct Ingame_Stage1_Scene_Meta
{
    static const TileMeta StageBackgroundEntity_Lvl1_TileMeta;
    static const TileMeta StageBackgroundEntity_Lvl2_TileMeta;
    static const TileMeta StageBackgroundEntity_Lvl3_TileMeta;
    static const TileMeta StageBackgroundEntity_Lvl4_TileMeta;
    static const TileMeta StageBackgroundEntity_Lvl5_TileMeta;
    static const TileMeta StageBackgroundEntity_Lvl6_TileMeta;

    static const TileMeta* LevelBGTileMetas[6];
};

class Ingame_Stage1_Scene : public Ingame_BasicStage_Scene
{
    public:
        Ingame_Stage1_Scene(SaveManager* aSaveManager);
        ~Ingame_Stage1_Scene();

        void LoadTileSets();
};
