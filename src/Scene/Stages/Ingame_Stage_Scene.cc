#include "Ingame_Stage_Scene.hpp"
#include "../../Manager/BitmapResourceManager.hpp"
#include "../../Manager/SoundResourceManager.hpp"
#include "../../Manager/SaveManager.hpp"
#include "../../Input/Ingame_InputProcessor.hpp"
#include "../../Entity/Generic/StaticPictureEntity.hpp"
#include "../../Entity/Generic/TileSetEntity.hpp"
#include "../../Entity/Stage/WallEntity.hpp"

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
    this->dwordA88 = 0;
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
    // TODO: holy fuck, this is a massive shit

    // TODO: check something in save flags??
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
        this->lampEntities[i] = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[27], nullptr, 0);
    }

    for (uint32_t i = 0; i < 8; i++)
    {
        // this->itemEntities[i] = new ItemEntity(this, this->sceneBitmapMgr->bitmapPtrs[23]);
    }

    // TODO: Create 100 score entities

    // TODO: Create cockpit texts
    this->hudTextEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[32], nullptr, 0);
    this->hudTextEntity->SetLayerIndex(4);
    this->hudTextEntity->dword10 = 0;

    this->gridImageEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[35], nullptr, 0);
    this->gridImageEntity->SetLayerIndex(3);
    this->gridImageEntity->coordinateLikeThingie = 100;
    this->gridImageEntity->dword10 = 0;

    // TODO: Create Score

    this->pauseTextEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[66], nullptr, 0);
    this->pauseTextEntity->SetLayerIndex(4);
    this->pauseTextEntity->dword10 = 0;

    // TODO: create pmark, hearts, hud??
}

void Ingame_Stage_Scene::AttachEntities()
{
    // TODO: Do something with save data and hudScoreP1 and P2
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

// ------ LogoEntity RenderMeta START ------
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

// ------ LogoEntity RenderMeta END ------
