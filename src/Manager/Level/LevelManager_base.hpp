#pragma once

class Ingame_Stage_Scene;

class LevelManager_base
{
    public:
        Ingame_Stage_Scene *Scene;
        int enemyFactories[32];

        LevelManager_base(Ingame_BasicStage_Scene *aScene);
        ~LevelManager_base();
};