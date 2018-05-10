#pragma once

#include <cstdint>
#include "Manager/Level/LevelManager_base.hpp"

class FontTileSetEntity;

class LevelManager_Normal : public LevelManager_base
{
    public:
        uint32_t dword88;
        uint8_t buffer8C[56];
        FontTileSetEntity* dwordC4;
        uint32_t dwordC8;
        uint32_t dwordCC;
        uint32_t dwordD0;
        uint32_t dwordD4;
        uint32_t dwordD8;
        uint32_t dwordDC;
        uint16_t wordE0;
        uint8_t levelPhase;
        uint32_t dwordE4;
        uint32_t dwordE8;

        LevelManager_Normal(Ingame_BasicStage_Scene* aScene);
        virtual ~LevelManager_Normal();

        virtual void F2() override;
        virtual void F3() override;
        virtual void F4() override;
        virtual void F5() override;
        virtual void F6() override;
        virtual void F7() override;
        virtual void F8();
        virtual void F9();
};
