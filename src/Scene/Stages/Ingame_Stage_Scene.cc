#include "Manager/BitmapResourceManager.hpp"
#include "Manager/SoundResourceManager.hpp"
#include "Manager/SaveManager.hpp"
#include "Input/Ingame_InputProcessor.hpp"
#include "Entity/Generic/StaticPictureEntity.hpp"
#include "Entity/Generic/TileSetEntity.hpp"
#include "Entity/Stage/WallEntity.hpp"
#include "Entity/Stage/ItemEntity.hpp"
#include "Entity/Stage/FloatingTextEntity.hpp"
#include "Entity/Stage/FontTileSetEntity.hpp"
#include "Scene/Stages/Ingame_Stage_Scene.hpp"

Ingame_Stage_Scene::Ingame_Stage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager)
    : GameScene(aPaletteDataBytes)
{
    this->saveManager = aSaveManager;
    this->dword90C = 0;
    this->dword910 = 0;
    this->sceneSoundMgr = nullptr;
    
    /*
    cPtr = (int)&this->hudPMark1;
    i = 2;

    do
    {
        *(_DWORD *)(cPtr + 64) = 0;                 // zero init 4 offseted buffers 2 times
                                                    // dword918, dword91C
        *(_DWORD *)cPtr = 0;                        // dword8D8, dword8DC
        *(_DWORD *)(cPtr + 0x19C) = 0;              // dwordA74, dwordA78
        *(_DWORD *)(cPtr + 0x1A4) = 0;              // dwordA7C, dwordA80
        cPtr += 4;
        --i;
    }
    while ( i );
    */

    memset(this->wallEntities, 0, sizeof(this->wallEntities));
    memset(this->hundredScoreEntities, 0, sizeof(this->hundredScoreEntities));
    memset(this->itemEntities, 0, sizeof(this->itemEntities));
    this->hudTextEntity = nullptr;
    this->scoreFontTileEntity = nullptr;
    this->gridImageEntity = nullptr;
    this->stageBackgroundTileSetEntity = nullptr;
    memset(this->wallBarEntities, 0, sizeof(this->wallBarEntities));
    memset(this->lampEntities, 0, sizeof(this->lampEntities));
    this->pauseTextEntity = nullptr;
    this->dword908 = 0;

    // TODO: check for save flag
    this->sceneBitmapMgr = new BitmapResourceManager(this->saveManager->nextStage + 7, this->palette2, 0);
    this->sceneSoundMgr = new SoundResourceManager(this->saveManager->nextStage + 7);
    this->CreateEntities();
    this->inputProcessor = new Ingame_InputProcessor(this->saveManager);
}

Ingame_Stage_Scene::~Ingame_Stage_Scene()
{
}

void Ingame_Stage_Scene::CreateEntities()
{
    // TODO: Create player entities based on player count
    // This includes hudPmarks, hud scores, and hud hearts

    uint32_t wallYOffsets[] = { 0x48, 0xB8, 0x128, 0x198 };
    uint32_t wallXOffsets[] = { 0x28, 0x78, 0xC8, 0x118, 0x168, 0x1B8, 0x208, 0x258 };

    for (uint32_t i = 0; i < 4; i++)
        for (uint32_t j = 0; j < 8; j++)
        {
            uint32_t wallIndex = (i * 8) + j;
            this->wallEntities[wallIndex] = new WallEntity(this, this->sceneBitmapMgr->bitmapPtrs[25], wallXOffsets[j], wallYOffsets[i]);
        }

    for (uint32_t i = 0; i < 4; i++)
        for (uint32_t j = 0; j < 9; j++)
        {
            uint32_t barIndex = (i * 9) + j;
            this->wallBarEntities[barIndex] = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[59], &Ingame_Stage_Scene_Meta::WallBarEntity_RenderMeta, 0);
        }

    for (uint32_t i = 0; i < 8; i++)
    {
        this->lampEntities[i] = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[27], &Ingame_Stage_Scene_Meta::LampEntity_RenderMeta, 0);
    }

    for (uint32_t i = 0; i < 8; i++)
    {
        // BMP_ITEM (Powerups + Coins)
        this->itemEntities[i] = new ItemEntity(this, this->sceneBitmapMgr->bitmapPtrs[23]);
    }

    for (uint32_t i = 0; i < 10; i++)
    {
        // BMP_MINI (100 numbers in blue & green)
        this->hundredScoreEntities[i] = new FloatingTextEntity(this, this->sceneBitmapMgr->bitmapPtrs[24]);
    }

    // BMP_COCKPIT - HUD text ("HI-SCORE", "STAGE TIME")
    this->hudTextEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[32], nullptr, 0);
    this->hudTextEntity->SetLayerIndex(4);
    this->hudTextEntity->dword10 = 0;

    // BMP_WINDOW - Grid image?
    this->gridImageEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[35], nullptr, 0);
    this->gridImageEntity->SetLayerIndex(3);
    this->gridImageEntity->coordinateLikeThingie = 100;
    this->gridImageEntity->dword10 = 0;

    this->scoreFontTileEntity = new FontTileSetEntity(this, this->sceneBitmapMgr->bitmapPtrs[21], 0);

    this->pauseTextEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[66], nullptr, 0);
    this->pauseTextEntity->SetLayerIndex(4);
    this->pauseTextEntity->dword10 = 0;
}

void Ingame_Stage_Scene::AttachEntities()
{
    // TODO: Loop over players and setup hudScoreP1 and hudScoreP2
    // TODO: Do something with save data and hudTextEntity

    uint32_t barYOffsets[] = { 0x48, 0xB8, 0x128, 0x198 };
    uint32_t barXOffsets[] = { 0, 0x50, 0xA0, 0xF0, 0x140, 0x190, 0x1E0, 0x230, 0x280 };
    uint16_t renderIndexes[] = { 1, 0, 0, 0, 0, 0, 0, 0, 2, 0 };

    for (uint32_t i = 0; i < 4; i++)
        for (uint32_t j = 0; j < 9; j++)
        {
            uint32_t barIndex = (i * 9) + j;

            if (this->wallBarEntities[barIndex] == nullptr)
                continue;

            this->wallBarEntities[barIndex]->AttachWithPosition(barXOffsets[j], barYOffsets[i], 0);
            this->wallBarEntities[barIndex]->renderDataPtrIndex = renderIndexes[j];
            this->wallBarEntities[barIndex]->AssignRenderRectangles(renderIndexes[j]);
            this->wallBarEntities[barIndex]->SetLayerIndex(1);
        }

    this->saveManager->lastStageStatus = 0;
    this->ticksLeftUntilReEval = 120;
    this->PaletteFadeInStart(1, 32);

    this->stageBackgroundTileSetEntity->Attach();
}

void Ingame_Stage_Scene::AttachLamps()
{
    uint32_t lampXOffsets[] = { 0x50, 0x230, 0x50, 0x230, 0x50, 0x230, 0x50, 0x230 };
    uint32_t lampYOffsets[] = { 0x28, 0x28,  0x98, 0x98, 0x108, 0x108, 0x178, 0x178 };

    for (uint32_t i = 0; i < 8; i++)
    {
        this->lampEntities[i]->AttachWithPosition(lampXOffsets[i], lampYOffsets[i], 0);
        this->lampEntities[i]->SetLayerIndex(1);
        this->lampEntities[i]->coordinateLikeThingie = 3;
        this->lampEntities[i]->renderDataPtrIndex = 2;
        this->lampEntities[i]->AssignRenderRectangles(2);
    }
}

// ------ WallBarEntity RenderMeta START ------
static const uint16_t WallBarEntity_RenderMeta_1_1[] =
{
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t WallBarEntity_RenderMeta_1_2[] =
{
    1,
    2,
    2,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t WallBarEntity_RenderMeta_1_3[] =
{
    1,
    3,
    3,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t* WallBarEntity_RenderMeta_1[] =
{
    &WallBarEntity_RenderMeta_1_1[0],
    &WallBarEntity_RenderMeta_1_2[0],
    &WallBarEntity_RenderMeta_1_3[0],
    0
};

static const MSRect WallBarEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 8, 0x58 }, // src rectangle
    { 4, 0, 8, 0x58 },
    { 0, 0, 4, 0x58 }
};

static const MSRect WallBarEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -4, -40, 4, 48 }, // lengths to sides (dimensions)
    { 0, -40, 4, 48 },
    { -4, -40, 0, 48 }
};

const RenderMeta Ingame_Stage_Scene_Meta::WallBarEntity_RenderMeta =
{
    &WallBarEntity_RenderMeta_1[0],
    &WallBarEntity_RenderMeta_2[0],
    &WallBarEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};

// ------ WallBarEntity RenderMeta END ------

// ------ LampEntity RenderMeta START ------
static const uint16_t LampEntity_RenderMeta_1_1[] =
{
    3,
    5,
    1,
    0,
    0,
    2,
    3,
    6,
    1,
    0,
    0,
    2,
    3,
    7,
    1,
    0,
    0,
    2,
    3,
    8,
    1,
    0,
    0,
    1
};

static const uint16_t LampEntity_RenderMeta_1_2[] =
{
    3,
    9,
    1,
    0,
    0,
    2,
    3,
    10,
    1,
    0,
    0,
    2,
    3,
    11,
    1,
    0,
    0,
    2,
    3,
    12,
    1,
    0,
    0,
    1
};

static const uint16_t LampEntity_RenderMeta_1_3[] =
{
    3,
    1,
    1,
    0,
    0,
    2,
    3,
    2,
    1,
    0,
    0,
    2,
    3,
    3,
    1,
    0,
    0,
    2,
    3,
    4,
    1,
    0,
    0,
    1
};

static const uint16_t* LampEntity_RenderMeta_1[] =
{
    &LampEntity_RenderMeta_1_1[0],
    &LampEntity_RenderMeta_1_2[0],
    &LampEntity_RenderMeta_1_3[0],
    0
};

static const MSRect LampEntity_RenderMeta_2[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { 0x00, 0x10, 0x18, 0x20 },
    { 0x00, 0x20, 0x18, 0x30 },
    { 0x00, 0x30, 0x18, 0x40 },
    { 0x00, 0x40, 0x18, 0x50 },
    { 0x18, 0x10, 0x30, 0x20 },
    { 0x18, 0x20, 0x30, 0x30 },
    { 0x18, 0x30, 0x30, 0x40 },
    { 0x18, 0x40, 0x30, 0x50 },
    { 0x30, 0x10, 0x48, 0x20 },
    { 0x30, 0x20, 0x48, 0x30 },
    { 0x30, 0x30, 0x48, 0x40 },
    { 0x30, 0x40, 0x48, 0x50 }
};

static const MSRect LampEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -12, -8, 12, 8 } // lengths to sides (dimensions)
};

const RenderMeta Ingame_Stage_Scene_Meta::LampEntity_RenderMeta =
{
    &LampEntity_RenderMeta_1[0],
    &LampEntity_RenderMeta_2[0],
    &LampEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};

// ------ LampEntity RenderMeta END ------
