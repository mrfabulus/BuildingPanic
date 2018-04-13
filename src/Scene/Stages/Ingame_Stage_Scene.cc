#include "Ingame_Stage_Scene.hpp"
#include "../../Manager/BitmapResourceManager.hpp"
#include "../../Manager/SoundResourceManager.hpp"
#include "../../Manager/SaveManager.hpp"
#include "../../Input/Ingame_InputProcessor.hpp"
#include "../../Entity/Generic/StaticPictureEntity.hpp"
#include "../../Entity/Generic/TileSetEntity.hpp"

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

    // TODO: Create walls
    // TODO: Create wall bars
    // TODO: Create lamps
    // TODO: Create items
    // TODO: Create 100 score entities
    // TODO: Create cockpit texts
    // TODO: Load grid
    // TODO: Create Score, pause, pmark, hearts, hud??
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
