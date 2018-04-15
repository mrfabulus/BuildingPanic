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
    this->tobiSelected = false;
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

bool CharacterChoiceScene::CreateEntities()
{
    this->inputProcessor = new MenuHandler_InputProcessor();
    this->sceneBitmapMgr = new BitmapResourceManager(3, nullptr, 0);
    this->sceneSoundMgr = new SoundResourceManager(3);

    this->stageSelectTiles = new TileSetEntity(this, this->sceneBitmapMgr->bitmapPtrs[58], &CharacterChoiceScene_Meta::BGSelect_TileMeta);
    this->selectTextEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[46], &CharacterChoiceScene_Meta::SelectTextEntity_RenderMeta, 0);
    this->selectSubtextsEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[49], &CharacterChoiceScene_Meta::SelectSubtextsEntity_RenderMeta, 0);
    this->selectionCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[67], &CharacterChoiceScene_Meta::SelectionCursorEntity_RenderMeta, 0);
    this->unknownStageSymbol1 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->unknownStageSymbol2 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->unknownStageSymbol3 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->player1PortraitEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[72], &CharacterChoiceScene_Meta::PlayerPortraitEntity_RenderMeta, 0);
    this->player2PortraitEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[72], &CharacterChoiceScene_Meta::PlayerPortraitEntity_RenderMeta, 0);

    return true;
}

void CharacterChoiceScene::Init()
{
    this->stageSelectTiles->Attach();
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
    uint32_t buildingXOffsets[] = { 0x80, 0xE0, 0x140, 0x1A0, 0x200 };
    
    // Retrieve how many stages were done according to the save file
    uint16_t buildingCount = *((uint16_t *)&this->saveMgr->rawSaveData[484]);

    switch (this->scenePhaseIndex)
    {
        case 0:
            if (this->ticksLeftUntilReEval <= 0)
            {
                this->selectSubtextsEntity->AttachWithPosition(320, 416, 0);
                this->selectionCursorEntity->AttachWithPosition(this->tobiSelected == false ? 0xB0 : 0x1D0, 240, 0);

                this->saveMgr->CreatePlayerObjects();

                // TODO: Take player count into account
                this->saveMgr->playerObject1.playerID = 0;
                // this->saveMgr->playerObject2->playerID = 1;

                this->saveMgr->nextStage = this->selectedStageNumber;
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
                this->saveMgr->playerObject1.playerID = (uint16_t) this->tobiSelected;

                // If there are 2 players, the other player is Tobi (who did not choose Doka)
                if (this->saveMgr->saveFlags & 2)
                    this->saveMgr->playerObject2.playerID = (uint16_t) (this->tobiSelected == false);

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
            else if ( (mask & 0x100010) != 0 && this->tobiSelected )
            {
                // left arrow pressed
                this->tobiSelected = false;

                if ( this->selectionCursorEntity->extraPositionDataBase )
                {
                    this->selectionCursorEntity->extraPositionDataBase->dCenterX = 0xB0;
                }

                this->selectionCursorEntity->centerX = 0xB0;
                // this->sceneSoundMgr->PlaySoundForDuration(1, 320);
            }
            else if ( (mask & 0x200020) != 0 && !this->tobiSelected)
            {
                // right arrow pressed
                this->tobiSelected = true;

                if ( this->selectionCursorEntity->extraPositionDataBase )
                {
                    this->selectionCursorEntity->extraPositionDataBase->dCenterX = 0x1D0;
                }

                this->selectionCursorEntity->centerX = 0x1D0;
                // this->sceneSoundMgr->PlaySoundForDuration(1, 320);
            }
            break;
        case 4098:
            // This is the initialization of the subscene where the player chooses one of the buildings to play on
            if (!this->fadeIn_active && !this->fadeAway_active)
            {
                this->selectSubtextsEntity->Detach();
                this->player1PortraitEntity->Detach();
                this->player2PortraitEntity->Detach();
                this->stageSelectTiles->Detach();

                if (this->stageSelectTiles != nullptr)
                {
                    delete this->stageSelectTiles;
                    this->stageSelectTiles = nullptr;
                }

                // BMP_BG_SELECT
                // TODO: Add tile meta
                this->stageSelectTiles = new TileSetEntity(this, this->sceneBitmapMgr->bitmapPtrs[58], nullptr);

                if (this->stageSelectTiles != nullptr)
                {
                    this->stageSelectTiles->Attach();

                    // Switch text to "STAGE SELECT"
                    this->selectTextEntity->renderDataPtrIndex = 1;
                    this->selectTextEntity->AssignRenderRectangles(1);

                    // Switch to other cursor shape that fits the buildings
                    this->selectionCursorEntity->renderDataPtrIndex = 1;
                    this->selectionCursorEntity->AssignRenderRectangles(1);

                    if (this->selectionCursorEntity->extraPositionDataBase != nullptr)
                    {
                        this->selectionCursorEntity->extraPositionDataBase->dCenterX = 0x80;
                    }

                    this->selectionCursorEntity->centerX = 0x80;

                    this->ticksLeftUntilReEval = 60;
                    this->PaletteFadeInStart(1, 32);

                    this->scenePhaseIndex = 4099;

                    // Sanity check against count
                    if ((buildingCount - 1) < 3)
                    {
                        // TODO: Clean this up
                        StaticPictureEntity** cEntity = (&this->unknownStageSymbol1) + (buildingCount - 1);

                        for (uint32_t i = (buildingCount - 1); i < 3; i++)
                        {
                            (*cEntity)->AttachWithPosition(buildingXOffsets[2 + (buildingCount - 1) + i], 256, 0);
                            cEntity++;
                        }
                    }
                }
            }
            break;
        case 4099:
            if (this->ticksLeftUntilReEval <= 0)
            {
                this->selectSubtextsEntity->AttachWithPosition(320, 416, 0);
                this->selectSubtextsEntity->renderDataPtrIndex = 1;
                this->selectSubtextsEntity->AssignRenderRectangles(1);
                this->scenePhaseIndex = 4100;
            }
            break;
        case 4100:
            // Choosing building (subscene constructed, receiving input)
            if ((mask & 0x10001) != 0)
            {
                // Enter pressed
                // this->sceneSoundMgr->PlaySoundForDuration(0, 320);
                
                this->selectionCursorEntity->renderDataPtrIndex = 3;
                this->selectionCursorEntity->AssignRenderRectangles(3);

                this->selectSubtextsEntity->renderDataPtrIndex = 2;
                this->selectSubtextsEntity->AssignRenderRectangles(2);
                
                this->scenePhaseIndex = 2;
            }
            else if ( (mask & 0x100010) != 0 && this->selectedStageNumber > 0)
            {
                // left arrow pressed
                this->selectedStageNumber--;

                if (this->selectionCursorEntity->extraPositionDataBase != nullptr)
                {
                    this->selectionCursorEntity->extraPositionDataBase->dCenterX = buildingXOffsets[this->selectedStageNumber];
                }

                this->selectionCursorEntity->centerX = buildingXOffsets[this->selectedStageNumber];
                // this->sceneSoundMgr->PlaySoundForDuration(1, 320);
            }
            else if ( (mask & 0x200020) != 0 && this->selectedStageNumber < buildingCount)
            {
                // right arrow pressed
                this->selectedStageNumber++;

                if (this->selectionCursorEntity->extraPositionDataBase != nullptr)
                {
                    this->selectionCursorEntity->extraPositionDataBase->dCenterX = buildingXOffsets[this->selectedStageNumber];
                }

                this->selectionCursorEntity->centerX = buildingXOffsets[this->selectedStageNumber];
                // this->sceneSoundMgr->PlaySoundForDuration(1, 320);
            }
            break;
    }
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

static const uint16_t* SelectTextEntity_RenderMeta_1[] =
{
    &SelectTextEntity_RenderMeta_1_1[0],
    &SelectTextEntity_RenderMeta_1_2[0],
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

const RenderMeta CharacterChoiceScene_Meta::SelectTextEntity_RenderMeta =
{
    &SelectTextEntity_RenderMeta_1[0],
    &SelectTextEntity_RenderMeta_2[0],
    &SelectTextEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
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

static const uint16_t* SelectSubtextsEntity_RenderMeta_1[] =
{
    &SelectSubtextsEntity_RenderMeta_1_1[0],
    &SelectSubtextsEntity_RenderMeta_1_2[0],
    &SelectSubtextsEntity_RenderMeta_1_3[0],
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

const RenderMeta CharacterChoiceScene_Meta::SelectSubtextsEntity_RenderMeta =
{
    &SelectSubtextsEntity_RenderMeta_1[0],
    &SelectSubtextsEntity_RenderMeta_2[0],
    &SelectSubtextsEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
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

static const uint16_t* SelectionCursorEntity_RenderMeta_1[] =
{
    &SelectionCursorEntity_RenderMeta_1_1[0],
    &SelectionCursorEntity_RenderMeta_1_2[0],
    &SelectionCursorEntity_RenderMeta_1_3[0],
    &SelectionCursorEntity_RenderMeta_1_4[0]
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

const RenderMeta CharacterChoiceScene_Meta::SelectionCursorEntity_RenderMeta =
{
    &SelectionCursorEntity_RenderMeta_1[0],
    &SelectionCursorEntity_RenderMeta_2[0],
    &SelectionCursorEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
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

static const uint16_t* PlayerPortraitEntity_RenderMeta_1[] =
{
    &PlayerPortraitEntity_RenderMeta_1_1[0],
    &PlayerPortraitEntity_RenderMeta_1_2[0],
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

const RenderMeta CharacterChoiceScene_Meta::PlayerPortraitEntity_RenderMeta =
{
    &PlayerPortraitEntity_RenderMeta_1[0],
    &PlayerPortraitEntity_RenderMeta_2[0],
    &PlayerPortraitEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ PlayerPortraitEntity RenderMeta END ------

// ------ BGSelect TileMeta START ------
static const uint16_t BGSelect_TileMeta_1[] =
{
    0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01,
    0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11,
    0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10,
    0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11,
    0x01, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x01, 0x11, 0x12, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x10, 0x11,
    0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x11, 0x11, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11,
    0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01,
    0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02,
    0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12,
    0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11,
    0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11,
    0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11,
    0x01, 0x02, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x02, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x02, 0x00, 0x01, 0x11, 0x12, 0x10, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x12, 0x10, 0x11, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x12, 0x10, 0x11,
    0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11,
    0x01, 0x02, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x02, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x02, 0x00, 0x01, 0x11, 0x12, 0x10, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x12, 0x10, 0x11, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x12, 0x10, 0x11,
    0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11,
    0x01, 0x02, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x02, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x02, 0x00, 0x01, 0x11, 0x12, 0x10, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x12, 0x10, 0x11, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x12, 0x10, 0x11,
    0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11,
    0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01,
    0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02,
    0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12,
    0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11,
    0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11,
    0x01, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x11, 0x11, 0x11, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x11, 0x11, 0x11,
    0x01, 0x02, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x01, 0x02, 0x00, 0x01, 0x11, 0x12, 0x10, 0x11, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x11, 0x12, 0x10, 0x11,
    0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01,
    0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02,
    0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x01, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12,
    0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11,
    0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11, 0x11, 0x11, 0x11, 0x12, 0x10, 0x11
};

const TileMeta CharacterChoiceScene_Meta::BGSelect_TileMeta =
{
    640,
    480,
    16,
    0,
    0,
    0,
    0,
    &BGSelect_TileMeta_1[0],
    &gConsts::TileMeta_StandardRects[0],
    0
};
// ------ BGSelect TileMeta END ------
