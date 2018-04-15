#pragma once

class Ingame_BasicStage_Scene;

class LevelManager_base
{
    public:
        Ingame_BasicStage_Scene *Scene;
        int enemyFactories[32];

        LevelManager_base(Ingame_BasicStage_Scene* aScene);
        ~LevelManager_base();
};