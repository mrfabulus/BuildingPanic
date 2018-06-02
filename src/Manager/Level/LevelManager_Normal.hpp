#pragma once

#include <cstdint>
#include "Manager/Level/LevelManager_base.hpp"

class FontTileSetEntity;
class StaticPictureEntity;

class LevelManager_Normal : public LevelManager_base
{
    public:
        StaticPictureEntity* dword88;
        StaticPictureEntity* buffer8C[14];
        FontTileSetEntity* dwordC4[2];
        uint32_t* dwordCC[4]; // ScoreTileSetEntity2*[]
        uint32_t dwordDC;
        uint16_t wordE0;
        uint8_t levelPhase;
        uint32_t dwordE4;
        uint32_t dwordE8;

        LevelManager_Normal(Ingame_BasicStage_Scene* aScene);
        virtual ~LevelManager_Normal();

        bool CreateEntities();
        void SetupLamps1();
        void SetupLamps2();

        virtual void F2() override;
        virtual void F3() override;
        virtual void F4() override;
        virtual void F5() override;
        virtual void F6() override;
        virtual void F7() override;
        virtual void F8();
        virtual void F9();
};
