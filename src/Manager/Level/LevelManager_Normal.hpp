#pragma once

#include <cstdint>
#include "Manager/Level/LevelManager_base.hpp"
#include "Globals.hpp"

class FontTileSetEntity;
class StaticPictureEntity;
class ScoreTileSetEntity2;

struct LevelManager_Normal_Meta
{
    static const RenderMeta WindowMsg_RenderMeta;
};

class LevelManager_Normal : public LevelManager_base
{
    public:
        StaticPictureEntity* dword88;
        StaticPictureEntity* buffer8C[14];
        FontTileSetEntity* dwordC4[2];
        ScoreTileSetEntity2* dwordCC[4];
        uint32_t dwordDC;
        uint16_t wordE0;
        uint8_t levelPhase;
        uint32_t dwordE4;
        uint32_t dwordE8;

        LevelManager_Normal(Ingame_BasicStage_Scene* aScene);
        virtual ~LevelManager_Normal();

        bool CreateEntities();
        void PrepareLevel();
        void PrepareWalls();

        virtual void F2() override;
        virtual void Init() override;
        virtual void Update() override;
        virtual void F5() override;
        virtual void F6() override;
        // virtual bool F7() not overridden
        virtual bool IsLevelOver();
        virtual void F9();
};
