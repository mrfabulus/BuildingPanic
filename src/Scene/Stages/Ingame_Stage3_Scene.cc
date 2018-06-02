#include "Entity/Generic/TileSetEntity.hpp"
#include "Manager/BitmapResourceManager.hpp"
#include "Scene/Stages/Ingame_Stage3_Scene.hpp"

Ingame_Stage3_Scene::Ingame_Stage3_Scene(SaveManager* aSaveManager)
    : Ingame_BasicStage_Scene(nullptr, aSaveManager)
{
    this->LoadTileSets();
    this->AttachEntities();
}

Ingame_Stage3_Scene::~Ingame_Stage3_Scene()
{
}

void Ingame_Stage3_Scene::LoadTileSets()
{
    // BMP_BG_STG01
    // TODO: Choose tile meta based on level number (this->saveManager->nextLevel)
    this->stageBackgroundTileSetEntity = new TileSetEntity(this, this->sceneBitmapMgr->bitmapPtrs[38], &Ingame_Stage3_Scene_Meta::StageBackgroundEntity_TileMeta);
}

// ------ StageBackgroundEntity TileMeta START ------
static const uint16_t StageBackgroundEntity_TileMeta_1[] =
{
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03,
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03,
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13,
    0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13,
    0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x2A, 0x2B, 0x2C,
    0x2D, 0x2E, 0x2F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x36, 0x37, 0x38,
    0x39, 0x3A, 0x3B, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x31, 0x32,
    0x33, 0x34, 0x35, 0x10, 0x10, 0x10, 0x10, 0x10, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x0C, 0x02,
    0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x1C, 0x12, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x26, 0x27, 0x28, 0x29, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x46, 0x47,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x4B, 0x4C, 0x4D, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x56, 0x57, 0x57, 0x58, 0x59, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x5B, 0x5C, 0x5D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x66, 0x67,
    0x67, 0x68, 0x69, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x6B, 0x6C, 0x6D, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x66, 0x67, 0x67, 0x68, 0x69, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03,
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03,
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13,
    0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13,
    0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13,
    0x6B, 0x6C, 0x6D, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x66, 0x67,
    0x67, 0x68, 0x69, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x4C, 0x4D, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x52, 0x53, 0x53, 0x54, 0x55, 0x6B, 0x6C, 0x6D, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x66, 0x67, 0x67, 0x68, 0x69, 0x5E, 0x5F, 0x10, 0x10, 0x5A,
    0x5B, 0x5B, 0x5C, 0x5D, 0x10, 0x10, 0x4E, 0x4F, 0x10, 0x10, 0x10, 0x62, 0x63, 0x63, 0x64, 0x65,
    0x6B, 0x6C, 0x6D, 0x5E, 0x5F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x4E, 0x4F, 0x10, 0x66, 0x67,
    0x67, 0x68, 0x69, 0x5E, 0x5F, 0x10, 0x10, 0x6A, 0x6B, 0x6B, 0x6C, 0x6D, 0x10, 0x5E, 0x5E, 0x5F,
    0x10, 0x10, 0x61, 0x62, 0x63, 0x63, 0x64, 0x65, 0x6B, 0x6C, 0x6D, 0x5E, 0x5F, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x5E, 0x5E, 0x5F, 0x10, 0x66, 0x67, 0x67, 0x68, 0x69, 0x5E, 0x5F, 0x60, 0x10, 0x6A,
    0x6B, 0x6B, 0x6C, 0x6D, 0x10, 0x5E, 0x5E, 0x5F, 0x61, 0x60, 0x60, 0x62, 0x63, 0x63, 0x64, 0x65,
    0x6B, 0x6C, 0x6D, 0x5E, 0x5F, 0x61, 0x60, 0x60, 0x60, 0x10, 0x5E, 0x5E, 0x5F, 0x60, 0x66, 0x67,
    0x67, 0x68, 0x69, 0x5E, 0x5F, 0x60, 0x60, 0x6A, 0x6B, 0x6B, 0x6C, 0x6D, 0x60, 0x5E, 0x5E, 0x5F,
    0x5E, 0x5F, 0x60, 0x62, 0x63, 0x63, 0x64, 0x65, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x0C, 0x02,
    0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12,
    0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x1C, 0x12, 0x6B, 0x6C, 0x6D, 0x5E, 0x5F, 0x60, 0x60, 0x60,
    0x60, 0x60, 0x5E, 0x5E, 0x43, 0x44, 0x45, 0x57, 0x58, 0x58, 0x59, 0x5E, 0x5F, 0x60, 0x60, 0x5A,
    0x5B, 0x5B, 0x5C, 0x5D, 0x60, 0x5E, 0x5E, 0x5F, 0x5E, 0x5F, 0x60, 0x62, 0x63, 0x63, 0x64, 0x65,
    0x6B, 0x6C, 0x6D, 0x5E, 0x5F, 0x52, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x54, 0x55, 0x67,
    0x67, 0x68, 0x69, 0x5E, 0x5F, 0x60, 0x60, 0x6A, 0x6B, 0x6B, 0x6C, 0x6D, 0x60, 0x5E, 0x5E, 0x5F,
    0x5E, 0x5F, 0x60, 0x62, 0x63, 0x63, 0x64, 0x65, 0x6B, 0x6C, 0x6D, 0x5E, 0x5F, 0x62, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x64, 0x65, 0x67, 0x67, 0x68, 0x69, 0x5E, 0x5F, 0x60, 0x60, 0x6A,
    0x6B, 0x6B, 0x6C, 0x6D, 0x60, 0x5E, 0x5E, 0x5F, 0x5E, 0x5F, 0x60, 0x62, 0x63, 0x63, 0x64, 0x65,
    0x6B, 0x6C, 0x6D, 0x5E, 0x5F, 0x62, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x64, 0x65, 0x67,
    0x67, 0x68, 0x69, 0x5E, 0x5F, 0x60, 0x60, 0x6A, 0x6B, 0x6B, 0x6C, 0x6D, 0x60, 0x5E, 0x5E, 0x5F,
    0x5E, 0x5F, 0x60, 0x62, 0x63, 0x63, 0x64, 0x65, 0x6B, 0x6C, 0x6D, 0x5E, 0x5F, 0x62, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x64, 0x65, 0x67, 0x67, 0x68, 0x69, 0x5E, 0x5F, 0x60, 0x60, 0x6A,
    0x6B, 0x6B, 0x6C, 0x6D, 0x60, 0x5E, 0x5E, 0x5F, 0x5E, 0x5F, 0x60, 0x62, 0x63, 0x63, 0x64, 0x65,
    0x01, 0x04, 0x05, 0x06, 0x02, 0x0C, 0x0D, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03,
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03,
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x11, 0x14, 0x15, 0x16, 0x12, 0x1C, 0x1D, 0x13,
    0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13,
    0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13
};

const TileMeta Ingame_Stage3_Scene_Meta::StageBackgroundEntity_TileMeta =
{
    640,
    480,
    16,
    0,
    0,
    0,
    0,
    &StageBackgroundEntity_TileMeta_1[0],
    &gConsts::TileMeta_StandardRects[0],
    0
};
// ------ StageBackgroundEntity TileMeta END ------
