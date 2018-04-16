#pragma once

class Ingame_BasicStage_Scene;

class LevelManager_base
{
    public:
        Ingame_BasicStage_Scene* Scene;
        int enemyFactories[32];

        LevelManager_base(Ingame_BasicStage_Scene* aScene);
        virtual ~LevelManager_base();

        virtual void F2() = 0;
        virtual void F3() = 0;
        virtual void F4() = 0;
        virtual void F5() = 0;
        virtual void F6() = 0;
        virtual void F7() = 0;
};