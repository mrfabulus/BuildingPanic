#pragma once

#include "../GameScene.hpp"
#include "../../SDL2_Interface.hpp"
#include <cstdint>

class StaticPictureEntity;
class SaveManager;
class WallEntity;
class ItemEntity;
class TileSetEntity;
class FloatingTextEntity;
class FontTileSetEntity;
class BitmapResourceManager;
class SoundResourceManager;

struct Ingame_Stage_Scene_Meta
{
    static const RenderMeta WallBarEntity_RenderMeta;
    static const RenderMeta LampEntity_RenderMeta;
};

class Ingame_Stage_Scene : public GameScene
{
    public:
        StaticPictureEntity* hudPMark1;
        StaticPictureEntity* hudPMark2;
        FloatingTextEntity* hundredScoreEntities[10];
        uint32_t dword908;
        uint32_t dword90C;
        uint32_t dword910;
        SaveManager* saveManager;
        int32_t player1Entity;
        int32_t player2Entity;
        WallEntity* wallEntities[32];
        ItemEntity* itemEntities[8];
        TileSetEntity* stageBackgroundTileSetEntity;
        StaticPictureEntity* wallBarEntities[36];
        StaticPictureEntity* lampEntities[8];
        int32_t hudScoreP1;
        int32_t hudScoreP2;
        int32_t hudHeartP1;
        int32_t hudHeartP2;
        StaticPictureEntity* hudTextEntity;
        FontTileSetEntity* scoreFontTileEntity;
        StaticPictureEntity* pauseTextEntity;
        StaticPictureEntity* gridImageEntity;
        BitmapResourceManager* sceneBitmapMgr;
        SoundResourceManager* sceneSoundMgr;

        Ingame_Stage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager);
        virtual ~Ingame_Stage_Scene();

        void CreateEntities();
        void AttachEntities();
};
