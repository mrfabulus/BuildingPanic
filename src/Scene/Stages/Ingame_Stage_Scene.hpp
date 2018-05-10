#pragma once

#include <cstdint>
#include "SDL2_Interface.hpp"
#include "Scene/GameScene.hpp"

class StaticPictureEntity;
class SaveManager;
class WallEntity;
class ItemEntity;
class TileSetEntity;
class FloatingTextEntity;
class FontTileSetEntity;
class PlayerEntity;
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
        PlayerEntity* player1Entity;
        PlayerEntity* player2Entity;
        WallEntity* wallEntities[32];
        ItemEntity* itemEntities[8];
        TileSetEntity* stageBackgroundTileSetEntity;
        StaticPictureEntity* wallBarEntities[36];
        StaticPictureEntity* lampEntities[8];
        StaticPictureEntity* hudScoreP1;
        StaticPictureEntity* hudScoreP2;
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

        virtual int GetNextSceneIDReference() override;
        // virtual void MakeSureImagesAreReady()
        // virtual void UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount)
        virtual void Update() override;
        virtual void AttachEntities();

        void CreateBaseEntities();
        void AttachBaseEntities();
        void AttachLamps();
};
