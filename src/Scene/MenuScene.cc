#include "MenuScene.hpp"
#include "../Entity/UI/IntroCutSceneEntity.hpp"
#include "../Entity/Generic/StaticPictureEntity.hpp"
#include "../Manager/SaveManager.hpp"
#include "../Manager/BitmapResourceManager.hpp"
#include "../Manager/SoundResourceManager.hpp"
#include "../Input/MenuScene_InputProcessor.hpp"
#include <iostream>

uint32_t menuCursorYCoordinates[] = { 0x100, 0x120, 0x140, 0x160 };

MenuScene::MenuScene(SaveManager* aSaveManager)
    : GameScene(gConsts::misc_PaletteDataPtr)
{
    this->saveManager = aSaveManager;
    this->cutScenePhase = 1;
    this->menuChoice = 0;
    this->cutSceneRenderDataPtrIndex = 0;
    this->dword8E0 = 4; // remaining cutScene fast character changes
    this->byte958 = 0;
    this->byte959 = 0;
    this->gap8D8 = 0;

    this->inputProcessorMenu = nullptr;

    this->titleEntity = nullptr;
    this->yamadaCopyrightEntity = nullptr;
    this->menuOptionsEntity = nullptr;
    this->optionLabelEntity = nullptr;
    this->menuCursorEntity = nullptr;
    this->selectCursorEntity = nullptr;
    this->introCutSceneObject = nullptr;
    this->fontCharsetEntity = nullptr;

    memset(this->fontGlyphEntities, 0, sizeof(this->fontGlyphEntities));
    this->sceneBitmapMgr = new BitmapResourceManager(1, nullptr, 0);
    this->sceneSoundMgr = new SoundResourceManager(1);
    this->CreateEntities();

    this->ticksLeftUntilReEval = 90;
    // TODO: start playing menu midi (Bpbgm01.mid)
}

MenuScene::~MenuScene()
{
}

void MenuScene::CreateEntities()
{
    this->inputProcessorMenu = new MenuScene_InputProcessor();
    this->inputProcessor = this->inputProcessorMenu;

    this->titleEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[44], &MenuScene_Meta::TitleEntity_RenderMeta, 0);
    this->yamadaCopyrightEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[54], &MenuScene_Meta::YamadaCopyrightEntity_RenderMeta, 0);
    this->menuOptionsEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[53], &MenuScene_Meta::MenuOptionsEntity_RenderMeta, 0);
    this->optionLabelEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[80], &MenuScene_Meta::OptionLabelEntity_RenderMeta, 0);
    this->menuCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[33], &MenuScene_Meta::MenuCursorEntity_RenderMeta, 0);
    this->selectCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[37], &MenuScene_Meta::SelectCursorEntity_RenderMeta, 0);

    this->introCutSceneObject = new IntroCutSceneEntity(this, this->sceneBitmapMgr->bitmapPtrs[71]);

    // TODO: Setup fontCharsetEntity
    // this->fontCharsetEntity->SetLayerIndex(4);

    // TODO: Setup fontGlyphEntities
}

int MenuScene::GetNextSceneIDReference()
{
    return (this->menuChoice != 0xFF) + 2;
}

void MenuScene::MakeSureImagesAreReady()
{
    // I don't think we need to implement this for SDL
}

/*
void MenuScene::UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount)
{
}
*/

void MenuScene::Update()
{
    /*
    std::cout << "MenuScene::Update SPI " << this->scenePhaseIndex << " TL " << this->ticksLeftUntilReEval;
    std::cout << " CSP " << (int) this->cutScenePhase << std::endl;
    */

    uint32_t mask = this->inputProcessor->newButtonPressesMask;

    switch (this->scenePhaseIndex)
    {
        case 0:
            if (this->ticksLeftUntilReEval <= 0)
                this->scenePhaseIndex = 0x10;
            break;
        case 2:
            if (!this->fadeIn_active && !this->fadeAway_active)
            {
                // TODO: SaveManager interaction
                this->finished = true;
            }
            break;
        case 0x10:
            if (this->cutScenePhase != 8 && this->inputProcessor->newButtonPressesMask & 0x10001 != 0)
            {
                // If the cutscene is not over and enter is pressed, we'll skip
                this->PaletteFadeAwayStart(1, 32);
                this->scenePhaseIndex = 0x11;
            }

            switch (this->cutScenePhase)
            {
                case 1:
                    this->InitCutSceneObject();
                    break;
                case 2:
                    this->CutSceneObject_F2();
                    break;
                case 3:
                    this->CutSceneObject_F3();
                    break;
                case 4:
                    this->CutSceneObject_F4();
                    break;
                case 5:
                    this->CutSceneObject_F5();
                    break;
                case 6:
                    this->CutSceneObject_F6(); // eval if fast changes are remaining and go to 5 or 7
                    break;
                case 7:
                    this->CutSceneObject_F2(); // back to Doka before menu init
                    break;
                case 8:
                    this->InitMainMenu();
                    break;
                default:
                    break;
            }

            break;
        case 0x11:
            // Cutscene skip
            if (!this->fadeIn_active && !this->fadeAway_active)
            {
                // Reset back to Doka's head
                this->introCutSceneObject->F_4146A0(0);

                // Go back to state 0x10 so the menu gets initialized
                this->scenePhaseIndex = 0x10;
                this->cutScenePhase = 8;
                this->ticksLeftUntilReEval = 45;
                this->PaletteFadeInStart(1, 32);
            }
            break;
        case 0x12:
            // Time expired, go into DemoPlay mode
            if (this->ticksLeftUntilReEval <= 0)
            {
                this->menuChoice = 0xFF;
                this->PaletteFadeAwayStart(1, 32);
                this->scenePhaseIndex = 2;
                return;
            }

            // Menu fully loaded, handling user input
            if ((mask & 0x10001) != 0)
            {
                // ENTER
                // TODO: Play sound slot 0

                if (this->menuChoice == 2)
                {
                    this->cutScenePhase = 1;
                    this->scenePhaseIndex = 0x13;
                }
                else
                {
                    // TODO: Set 1Por2P mode in saveManager
                    this->scenePhaseIndex = 2;
                }
            }
            else if ((mask & 0x400040) != 0)
            {
                // UP
                if (this->menuChoice == 0)
                    return;

                // TODO: Play sound slot 1

                this->menuChoice--;
                this->ticksLeftUntilReEval = 1800;

                if (this->menuCursorEntity->extraPositionDataBase != nullptr)
                {
                    this->menuCursorEntity->extraPositionDataBase->dCenterY = menuCursorYCoordinates[this->menuChoice];
                }

                this->menuCursorEntity->centerY = menuCursorYCoordinates[this->menuChoice];
            }
            else if ((mask & 0x800080) != 0)
            {
                // DOWN
                if (this->menuChoice == 2)
                    return;

                // TODO: Play sound slot 1

                this->menuChoice++;
                this->ticksLeftUntilReEval = 1800;

                if (this->menuCursorEntity->extraPositionDataBase != nullptr)
                {
                    this->menuCursorEntity->extraPositionDataBase->dCenterY = menuCursorYCoordinates[this->menuChoice];
                }

                this->menuCursorEntity->centerY = menuCursorYCoordinates[this->menuChoice];
            }

            break;
        case 0x13:
            // TODO: Handle "OPTION" subscene rendering
            break;
        default:
            break;
    }
}

void MenuScene::InitCutSceneObject()
{
    this->introCutSceneObject->AttachWithPosition(0, 0, 0);
    this->introCutSceneObject->Custom_AssignRenderRectangles(this->cutSceneRenderDataPtrIndex);
    this->cutScenePhase++;
}

void MenuScene::CutSceneObject_F2()
{
    if (this->introCutSceneObject->byte65 != 0)
    {
        this->ticksLeftUntilReEval = 90;
        this->cutScenePhase++;
    }
}

void MenuScene::CutSceneObject_F3()
{
    if (this->ticksLeftUntilReEval <= 0)
    {
        this->introCutSceneObject->F_4146D0();
        this->cutScenePhase++;
    }
}

void MenuScene::CutSceneObject_F4()
{
    if (this->introCutSceneObject->byte66 != 0)
    {
        this->cutSceneRenderDataPtrIndex++;

        if (this->cutSceneRenderDataPtrIndex == 2)
        {
            this->ticksLeftUntilReEval = 20;
            this->cutScenePhase++;
        }
        else
        {
            this->cutScenePhase = 2;
        }

        this->introCutSceneObject->Custom_AssignRenderRectangles(this->cutSceneRenderDataPtrIndex);
    }
}

void MenuScene::CutSceneObject_F5()
{
    if (this->introCutSceneObject->byte65 != 0 && this->ticksLeftUntilReEval <= 0)
    {
        this->introCutSceneObject->F_4146D0();
        this->cutScenePhase++;
    }
}

void MenuScene::CutSceneObject_F6()
{
    if (this->introCutSceneObject->byte66 != 0)
    {
        this->dword8E0--;

        if (this->dword8E0 != 0)
        {
            this->cutSceneRenderDataPtrIndex++;

            if (this->cutSceneRenderDataPtrIndex == 3)
            {
                this->cutSceneRenderDataPtrIndex = 0;
            }

            this->cutScenePhase = 5;
            this->ticksLeftUntilReEval = 20;
        }
        else
        {
            this->cutSceneRenderDataPtrIndex = 0;
            this->cutScenePhase = 7;
        }

        this->introCutSceneObject->Custom_AssignRenderRectangles(this->cutSceneRenderDataPtrIndex);
    }
}

void MenuScene::InitMainMenu()
{
    if (this->ticksLeftUntilReEval <= 0)
    {
        this->titleEntity->AttachWithPosition(320, 140, 0);
        this->yamadaCopyrightEntity->AttachWithPosition(320, 448, 0);
        this->menuOptionsEntity->AttachWithPosition(320, 288, 0);
        this->optionLabelEntity->AttachWithPosition(280, 320, 0);
        this->menuCursorEntity->AttachWithPosition(208, menuCursorYCoordinates[this->menuChoice], 0);

        // Go to next phase
        this->ticksLeftUntilReEval = 1800;
        this->scenePhaseIndex = 0x12;

        std::cout << "MenuScene::InitMainMenu" << std::endl;
    }
}

// ------ TitleEntity RenderMeta START ------
static const uint16_t TitleEntity_RenderMeta_1_1[] =
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

static const uint16_t* TitleEntity_RenderMeta_1[] =
{
    &TitleEntity_RenderMeta_1_1[0],
    0
};

static const MSRect TitleEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 560, 160 } // src rectangle
};

static const MSRect TitleEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -280, -80, 280, 80 } // lengths to sides (dimensions)
};

const RenderMeta MenuScene_Meta::TitleEntity_RenderMeta =
{
    &TitleEntity_RenderMeta_1[0],
    &TitleEntity_RenderMeta_2[0],
    &TitleEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ TitleEntity RenderMeta END ------

// ------ YamadaCopyrightEntity RenderMeta START ------
static const uint16_t YamadaCopyrightEntity_RenderMeta_1_1[] =
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

static const uint16_t* YamadaCopyrightEntity_RenderMeta_1[] =
{
    &YamadaCopyrightEntity_RenderMeta_1_1[0],
    0
};

static const MSRect YamadaCopyrightEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0x100, 8 } // src rectangle
};

static const MSRect YamadaCopyrightEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -128, -4, 128, 4 } // lengths to sides (dimensions)
};

const RenderMeta MenuScene_Meta::YamadaCopyrightEntity_RenderMeta =
{
    &YamadaCopyrightEntity_RenderMeta_1[0],
    &YamadaCopyrightEntity_RenderMeta_2[0],
    &YamadaCopyrightEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ YamadaCopyrightEntity RenderMeta END ------

// ------ MenuOptionsEntity RenderMeta START ------
static const uint16_t MenuOptionsEntity_RenderMeta_1_1[] =
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

static const uint16_t MenuOptionsEntity_RenderMeta_1_2[] =
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

static const uint16_t* MenuOptionsEntity_RenderMeta_1[] =
{
    &MenuOptionsEntity_RenderMeta_1_1[0],
    &MenuOptionsEntity_RenderMeta_1_2[0],
    0,
    0
};

static const MSRect MenuOptionsEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0xB8, 0x30 }, // src rectangle
    { 0, 0, 0xB8, 0x50 }
};

static const MSRect MenuOptionsEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -92, -40, 92, 8 }, // lengths to sides (dimensions)
    { -92, -40, 92, 40 }
};

const RenderMeta MenuScene_Meta::MenuOptionsEntity_RenderMeta =
{
    &MenuOptionsEntity_RenderMeta_1[0],
    &MenuOptionsEntity_RenderMeta_2[0],
    &MenuOptionsEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ MenuOptionsEntity RenderMeta END ------

// ------ OptionLabelEntity RenderMeta START ------
static const uint16_t OptionLabelEntity_RenderMeta_1_1[] =
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

static const uint16_t* OptionLabelEntity_RenderMeta_1[] =
{
    &OptionLabelEntity_RenderMeta_1_1[0],
    0
};

static const MSRect OptionLabelEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0x60, 0x10 } // src rectangle
};

static const MSRect OptionLabelEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -48, -8, 48, 8 }, // lengths to sides (dimensions)
};

const RenderMeta MenuScene_Meta::OptionLabelEntity_RenderMeta =
{
    &OptionLabelEntity_RenderMeta_1[0],
    &OptionLabelEntity_RenderMeta_2[0],
    &OptionLabelEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ OptionLabelEntity RenderMeta END ------

// ------ MenuCursorEntity RenderMeta START ------
static const uint16_t MenuCursorEntity_RenderMeta_1_1[] =
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

static const uint16_t MenuCursorEntity_RenderMeta_1_2[] =
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

static const uint16_t MenuCursorEntity_RenderMeta_1_3[] =
{
    1,
    3,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t* MenuCursorEntity_RenderMeta_1[] =
{
    &MenuCursorEntity_RenderMeta_1_1[0],
    &MenuCursorEntity_RenderMeta_1_2[0],
    &MenuCursorEntity_RenderMeta_1_3[0],
    0
};

static const MSRect MenuCursorEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0x20, 0x18 }, // src rectangle
    { 0x20, 0, 0x38, 0x18 },
    { 0x38, 0, 0x58, 0x18 }
};

static const MSRect MenuCursorEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -16, -12, 16, 12 }, // lengths to sides (dimensions)
    { -12, -12, 12, 12 }
};

const RenderMeta MenuScene_Meta::MenuCursorEntity_RenderMeta =
{
    &MenuCursorEntity_RenderMeta_1[0],
    &MenuCursorEntity_RenderMeta_2[0],
    &MenuCursorEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ MenuCursorEntity RenderMeta END ------

// ------ SelectCursorEntity RenderMeta START ------
static const uint16_t SelectCursorEntity_RenderMeta_1_1[] =
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

static const uint16_t SelectCursorEntity_RenderMeta_1_2[] =
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

static const uint16_t* SelectCursorEntity_RenderMeta_1[] =
{
    &SelectCursorEntity_RenderMeta_1_1[0],
    &SelectCursorEntity_RenderMeta_1_2[0],
    0,
    0
};

static const MSRect SelectCursorEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0x10, 8 }, // src rectangle
    { 0x10, 0, 0x40, 8 }
};

static const MSRect SelectCursorEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -8, -4, 8, 4 }, // lengths to sides (dimensions)
    { -24, -4, 24, 4 }
};

const RenderMeta MenuScene_Meta::SelectCursorEntity_RenderMeta =
{
    &SelectCursorEntity_RenderMeta_1[0],
    &SelectCursorEntity_RenderMeta_2[0],
    &SelectCursorEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ SelectCursorEntity RenderMeta END ------
