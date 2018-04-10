#include "CharacterChoiceScene.hpp"
#include "../Entity/Generic/StaticPictureEntity.hpp"
#include "../Entity/Generic/TileSetEntity.hpp"
#include "../Manager/SaveManager.hpp"
#include "../Manager/BitmapResourceManager.hpp"
#include "../Manager/SoundResourceManager.hpp"
#include "../Input/MenuHandler_InputProcessor.hpp"

CharacterChoiceScene::CharacterChoiceScene(SaveManager* aSaveManager)
    : GameScene(nullptr)
{
    this->byte8D8 = 0;
    this->selectedStageNumber = 0;
    this->dword8DC = 60;
    this->saveMgr = aSaveManager;
    this->sceneBitmapMgr = nullptr;
    this->sceneSoundMgr = nullptr;
    this->stageSelectTiles = nullptr;
    this->selectTextEntity = nullptr;
    this->selectSubtextsEntity = nullptr;
    this->selectionCursorEntity = nullptr;
    this->player1PortraitEntity = nullptr;
    this->player2PortraitEntity = nullptr;
    this->unknownStageSymbol1 = nullptr;
    this->unknownStageSymbol2 = nullptr;
    this->unknownStageSymbol3 = nullptr;

    if (this->CreateEntities())
    {
        this->Init();
    }
    else
    {
        this->init_OK = false;
    }
}

CharacterChoiceScene::~CharacterChoiceScene()
{
    // TODO: stop current MIDI

    if (this->player1PortraitEntity != nullptr)
    {
        delete this->player1PortraitEntity;
        this->player1PortraitEntity = nullptr;
    }

    if (this->player2PortraitEntity != nullptr)
    {
        delete this->player2PortraitEntity;
        this->player2PortraitEntity = nullptr;
    }

    if (this->unknownStageSymbol1 != nullptr)
    {
        delete this->unknownStageSymbol1;
        this->unknownStageSymbol1 = nullptr;
    }

    if (this->unknownStageSymbol2 != nullptr)
    {
        delete this->unknownStageSymbol2;
        this->unknownStageSymbol2 = nullptr;
    }

    if (this->unknownStageSymbol3 != nullptr)
    {
        delete this->unknownStageSymbol3;
        this->unknownStageSymbol3 = nullptr;
    }

    if (this->selectionCursorEntity != nullptr)
    {
        delete this->selectionCursorEntity;
        this->selectionCursorEntity = nullptr;
    }

    if (this->selectSubtextsEntity != nullptr)
    {
        delete this->selectSubtextsEntity;
        this->selectSubtextsEntity = nullptr;
    }

    if (this->selectTextEntity != nullptr)
    {
        delete this->selectTextEntity;
        this->selectTextEntity = nullptr;
    }

    if (this->stageSelectTiles != nullptr)
    {
        delete this->stageSelectTiles;
        this->stageSelectTiles = nullptr;
    }

    if (this->sceneSoundMgr != nullptr)
    {
        delete this->sceneSoundMgr;
        this->sceneSoundMgr = nullptr;
    }

    if (this->sceneBitmapMgr != nullptr)
    {
        delete this->sceneBitmapMgr;
        this->sceneBitmapMgr = nullptr;
    }

    if (this->inputProcessor != nullptr)
    {
        delete this->inputProcessor;
        this->inputProcessor = nullptr;
    }
}

int32_t CharacterChoiceScene::GetNextSceneIDReference()
{
    this->saveMgr->nextStage = this->selectedStageNumber;
    // Note: this is originally done via a reference array of numbers [7, 8, 9, 0xA, 0xB][nextStage]
    return this->saveMgr->nextStage + 7;
}

void CharacterChoiceScene::MakeSureImagesAreReady()
{
    // I don't think we need to implement this for SDL
}

void CharacterChoiceScene::Update()
{
    uint32_t mask = this->inputProcessor->newButtonPressesMask;

    switch (this->scenePhaseIndex)
    {
        case 0:
            if (this->ticksLeftUntilReEval <= 0)
            {
                this->selectSubtextsEntity->AttachWithPosition(320, 416, 0);
                this->selectionCursorEntity->AttachWithPosition(this->byte8D8 == 0 ? 0xB0 : 0x1D0, 240, 0);

                /*
                SaveManager_createPlayerObjects(this->saveMgr);// create human player objects
                v6 = this->saveMgr;
                v7 = 0;
                if ( ((v6->saveFlags & 0x202) != 0) + 1 > 0 )
                {
                    v8 = 24;
                    do
                    {
                        *((_BYTE *)&v6->VTable + v8) = v7;
                        v6 = this->saveMgr;
                        ++v7;
                        v8 += 12;
                    }
                    while ( v7 < ((v6->saveFlags & 0x202) != 0) + 1 );
                }
                inputCodes = (int)this->saveMgr;
                *(_WORD *)(inputCodes + 4) = this->selectedStageNumber;
                */

                this->saveMgr->nextLevel = 0;
                this->scenePhaseIndex = 4097;
            }
            break;
        case 2:
            this->dword8DC--;

            if (this->dword8DC == 0)
            {
                this->PaletteFadeAwayStart(1, 0x40);
            }
            else if (this->dword8DC < 0 && !this->fadeIn_active && !this->fadeAway_active)
            {
                // TODO: Set 2 values in this->saveMgr->gap10
                this->finished = true;
            }
            break;
        case 4097:
            if ((mask & 0x10001) != 0)
            {
                // Enter pressed
                this->saveMgr->playerObject1.isPlayerControlled = this->byte8D8;

                if (this->saveMgr->saveFlags & 2)
                    this->saveMgr->playerObject2.isPlayerControlled = this->byte8D8 == 0;

                this->selectionCursorEntity->renderDataPtrIndex = 2;
                this->selectionCursorEntity->AssignRenderRectangles(2);

                // Check if there is any known progress in the save file (completed at least stage 1)
                if ( *((uint16_t *)&this->saveMgr->rawSaveData[484]) != 0)
                {
                    // Go to building selection
                    this->scenePhaseIndex = 4098;
                }
                else
                {
                    // Scene ending shortly
                    this->scenePhaseIndex = 2;
                    this->selectSubtextsEntity->renderDataPtrIndex = 2;
                    this->selectSubtextsEntity->AssignRenderRectangles(2);
                }

                this->PaletteFadeAwayStart(1, 0x40u);
                // this->sceneSoundMgr->PlaySoundForDuration(0, 320);
            }
            else if ( (mask & 0x100010) != 0 && this->byte8D8 == 1 )
            {
                // left arrow pressed
                this->byte8D8 = 0;

                if ( this->selectionCursorEntity->extraPositionData )
                {
                    this->selectionCursorEntity->extraPositionData->dCenterX = 0xB0;
                }

                this->selectionCursorEntity->centerX = 0xB0;
                // this->sceneSoundMgr->PlaySoundForDuration(1, 320);
            }
            else if ( (mask & 0x200020) != 0 && this->byte8D8 == 0)
            {
                // right arrow pressed
                this->byte8D8 = 1;

                if ( this->selectionCursorEntity->extraPositionData )
                {
                    this->selectionCursorEntity->extraPositionData->dCenterX = 0x1D0;
                }

                this->selectionCursorEntity->centerX = 0x1D0;
                // this->sceneSoundMgr->PlaySoundForDuration(1, 320);
            }
            break;
        case 4098:
            if (!this->fadeIn_active && !this->fadeAway_active)
            {
                this->selectSubtextsEntity->Detach();
                this->player1PortraitEntity->Detach();
                this->player2PortraitEntity->Detach();

                /*
                this->stageSelectTiles->Detach();

                if (this->stageSelectTiles != nullptr)
                {
                    delete this->stageSelectTiles;
                }

                // BMP_BG_SELECT
                this->stageSelectTitles = new TileSetEntity();
                */

                if (this->stageSelectTiles != nullptr)
                {
                    this->stageSelectTiles->Attach();

                    this->selectTextEntity->renderDataPtrIndex = 1;
                    this->selectTextEntity->AssignRenderRectangles(1);

                    // this->selectionCursorEntity
                }
            }
            break;
        case 4099:
            break;
        case 5000:
            break;
    }
}

bool CharacterChoiceScene::CreateEntities()
{
    this->inputProcessor = new MenuHandler_InputProcessor();
    this->sceneBitmapMgr = new BitmapResourceManager(3, nullptr, 0);
    this->sceneSoundMgr = new SoundResourceManager(3);

    // TODO: Create stageSelectTiles

    this->selectTextEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[46], CharacterChoiceScene_RenderMeta::SelectTextEntityPtr, 0);
    this->selectSubtextsEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[49], CharacterChoiceScene_RenderMeta::SelectSubtextsEntityPtr, 0);
    this->selectionCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[67], CharacterChoiceScene_RenderMeta::SelectionCursorEntityPtr, 0);
    this->unknownStageSymbol1 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->unknownStageSymbol2 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->unknownStageSymbol3 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->player1PortraitEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[72], CharacterChoiceScene_RenderMeta::PlayerPortraitEntityPtr, 0);
    this->player2PortraitEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[72], CharacterChoiceScene_RenderMeta::PlayerPortraitEntityPtr, 0);

    return true;
}

void CharacterChoiceScene::Init()
{
    // TODO: Initialize stageSelectTiles
    this->selectTextEntity->AttachWithPosition(320, 64, 0);

    this->player1PortraitEntity->AttachWithPosition(0xB0, 240, 0);
    this->player1PortraitEntity->renderDataPtrIndex = 0;
    this->player1PortraitEntity->AssignRenderRectangles(0);

    this->player2PortraitEntity->AttachWithPosition(0x1D0, 240, 0);
    this->player2PortraitEntity->renderDataPtrIndex = 1;
    this->player2PortraitEntity->AssignRenderRectangles(1);

    this->ticksLeftUntilReEval = 60;
    this->PaletteFadeInStart(1, 32);
    // TODO: start bpbgm02.mid
}

// ------ SelectTextEntity RenderMeta START ------
static const uint16_t SelectTextEntity_RenderMeta_1_1[] =
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

static const uint16_t SelectTextEntity_RenderMeta_1_2[] =
{
    1,
    2,
    1,
    0,
    0,
    0,
    0,
    0
};

static const void* SelectTextEntity_RenderMeta_1[] =
{
    &SelectTextEntity_RenderMeta_1_1,
    &SelectTextEntity_RenderMeta_1_2,
    0,
    0
};

static const MSRect SelectTextEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0x22C, 0x42 }, // src rectangle
    { 0, 0x42, 0x22C, 0x84 }
};

static const MSRect SelectTextEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -278, -33, 278, 33 } // lengths to sides (dimensions)
};

static const void* SelectTextEntity_RenderMeta[] =
{
    &SelectTextEntity_RenderMeta_1,
    &SelectTextEntity_RenderMeta_2,
    &SelectTextEntity_RenderMeta_3,
    ((void*) gConsts::RenderMetaTerminatorPtr)
};

const uint32_t** CharacterChoiceScene_RenderMeta::SelectTextEntityPtr = (const uint32_t**) SelectTextEntity_RenderMeta;
// ------ SelectTextEntity RenderMeta END ------

// ------ SelectSubtextsEntity RenderMeta START ------
static const uint16_t SelectSubtextsEntity_RenderMeta_1_1[] =
{
    0x10,
    1,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t SelectSubtextsEntity_RenderMeta_1_2[] =
{
    0x10,
    2,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t SelectSubtextsEntity_RenderMeta_1_3[] =
{
    0x10,
    3,
    2,
    0,
    0,
    2,
    0x10,
    0,
    0,
    0,
    0,
    1
};

static const void* SelectSubtextsEntity_RenderMeta_1[] =
{
    &SelectSubtextsEntity_RenderMeta_1_1,
    &SelectSubtextsEntity_RenderMeta_1_2,
    &SelectSubtextsEntity_RenderMeta_1_3,
    0
};

static const MSRect SelectSubtextsEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0x140, 0x28 }, // src rectangle
    { 0, 0x28, 0x140, 0x50 },
    { 0, 0x50, 0xF0, 0x60 }
};

static const MSRect SelectSubtextsEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -160, -20, 160, 20 }, // lengths to sides (dimensions)
    { -120, -8, 120, 8 }
};

static const void* SelectSubtextsEntity_RenderMeta[] =
{
    &SelectSubtextsEntity_RenderMeta_1,
    &SelectSubtextsEntity_RenderMeta_2,
    &SelectSubtextsEntity_RenderMeta_3,
    ((void*) gConsts::RenderMetaTerminatorPtr)
};

const uint32_t** CharacterChoiceScene_RenderMeta::SelectSubtextsEntityPtr = (const uint32_t**) SelectSubtextsEntity_RenderMeta;
// ------ SelectSubtextsEntity RenderMeta END ------

// ------ SelectionCursorEntity RenderMeta START ------
static const uint16_t SelectionCursorEntity_RenderMeta_1_1[] =
{
    0x10,
    1,
    1,
    0,
    0,
    2,
    0x10,
    0,
    0,
    0,
    0,
    1
};

static const uint16_t SelectionCursorEntity_RenderMeta_1_2[] =
{
    0x10,
    2,
    2,
    0,
    0,
    2,
    0x10,
    0,
    0,
    0,
    0,
    1
};

static const uint16_t SelectionCursorEntity_RenderMeta_1_3[] =
{
    2,
    1,
    1,
    0,
    0,
    2,
    2,
    0,
    0,
    0,
    0,
    1
};

static const uint16_t SelectionCursorEntity_RenderMeta_1_4[] =
{
    2,
    2,
    2,
    0,
    0,
    2,
    2,
    0,
    0,
    0,
    0,
    1
};

static const void* SelectionCursorEntity_RenderMeta_1[] =
{
    &SelectionCursorEntity_RenderMeta_1_1,
    &SelectionCursorEntity_RenderMeta_1_2,
    &SelectionCursorEntity_RenderMeta_1_3,
    &SelectionCursorEntity_RenderMeta_1_4
};

static const MSRect SelectionCursorEntity_RenderMeta_2[] =
{
    { 0x10, 0x10, 0x11, 0x11 },
    { 0, 0, 0xE0, 0xE0 }, // src rectangle
    { 0xE0, 0, 0x140, 0xE0 }
};

static const MSRect SelectionCursorEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -112, -112, 112, 112 }, // lengths to sides (dimensions)
    { -48, -112, 48, 112 }
};

static const void* SelectionCursorEntity_RenderMeta[] =
{
    &SelectionCursorEntity_RenderMeta_1,
    &SelectionCursorEntity_RenderMeta_2,
    &SelectionCursorEntity_RenderMeta_3,
    ((void*) gConsts::RenderMetaTerminatorPtr)
};

const uint32_t** CharacterChoiceScene_RenderMeta::SelectionCursorEntityPtr = (const uint32_t**) SelectionCursorEntity_RenderMeta;
// ------ SelectionCursorEntity RenderMeta END ------

// ------ PlayerPortraitEntity RenderMeta START ------
static const uint16_t PlayerPortraitEntity_RenderMeta_1_1[] =
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

static const uint16_t PlayerPortraitEntity_RenderMeta_1_2[] =
{
    1,
    2,
    1,
    0,
    0,
    0,
    0,
    0
};

static const void* PlayerPortraitEntity_RenderMeta_1[] =
{
    &PlayerPortraitEntity_RenderMeta_1_1,
    &PlayerPortraitEntity_RenderMeta_1_2,
    0,
    0
};

static const MSRect PlayerPortraitEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0xC0, 0xC0 }, // src rectangle
    { 0xC0, 0, 0x180, 0xC0 }
};

static const MSRect PlayerPortraitEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -96, -96, 96, 96 } // lengths to sides (dimensions)
};

static const void* PlayerPortraitEntity_RenderMeta[] =
{
    &PlayerPortraitEntity_RenderMeta_1,
    &PlayerPortraitEntity_RenderMeta_2,
    &PlayerPortraitEntity_RenderMeta_3,
    ((void*) gConsts::RenderMetaTerminatorPtr)
};

const uint32_t** CharacterChoiceScene_RenderMeta::PlayerPortraitEntityPtr = (const uint32_t**) PlayerPortraitEntity_RenderMeta;
// ------ PlayerPortraitEntity RenderMeta END ------
