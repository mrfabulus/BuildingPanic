#pragma once

#include <cstdint>

class Ingame_BasicStage_Scene;

enum LevelInfoType : uint8_t
{
    LevelInfoType_Terminator = 0,
    LevelInfoType_ItemInfo = 1,
    LevelInfoType_EnemyInfo = 2
};

struct LevelInfoEntry
{
    LevelInfoType infoType;
    uint8_t padding[3];
    uint32_t u2;
    uint32_t u3;
    uint16_t u4;
    uint8_t padding2[2];
};

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