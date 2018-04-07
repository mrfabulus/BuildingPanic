#include "MenuScene.hpp"
#include "../Entity/UI/IntroCutSceneEntity.hpp"
#include "../Entity/Generic/StaticPictureEntity.hpp"
#include "../Manager/SaveManager.hpp"
#include "../Manager/BitmapResourceManager.hpp"
#include "../Manager/SoundResourceManager.hpp"
#include "../Input/MenuScene_InputProcessor.hpp"
#include <iostream>

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

    this->inputProcessor = nullptr;

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
    this->inputProcessor = new MenuScene_InputProcessor();

    this->titleEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[44], MenuScene_RenderMeta::TitleEntity_RenderMetaPtr, 0);
    this->yamadaCopyrightEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[54], MenuScene_RenderMeta::YamadaCopyrightEntity_RenderMetaPtr, 0);
    this->menuOptionsEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[53], MenuScene_RenderMeta::MenuOptionsEntity_RenderMetaPtr, 0);
    this->optionLabelEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[80], nullptr, 0);
    this->menuCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[33], nullptr, 0);
    this->selectCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[37], nullptr, 0);

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
    // TODO: hoooly shit, this function..
    std::cout << "MenuScene::Update SPI " << this->scenePhaseIndex << " TL " << this->ticksLeftUntilReEval;
    std::cout << " CSP " << (int) this->cutScenePhase << std::endl;

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
            if (this->cutScenePhase != 8 && false /* && Enter pressed */)
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
            // Menu fully loaded, handling user input

            if (this->ticksLeftUntilReEval <= 0)
            {
                // Time expired, go into DemoPlay mode
                this->menuChoice = 0xFF;
                this->PaletteFadeAwayStart(1, 32);
                this->scenePhaseIndex = 2;
                return;
            }

            // TODO: Handle inputs from player (UP, DOWN, ENTER)

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
        this->menuCursorEntity->AttachWithPosition(208, 256, 0); // TODO: Y coord by this->menuChoice

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

static const void* TitleEntity_RenderMeta_1[] =
{
    &TitleEntity_RenderMeta_1_1,
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

static const void* TitleEntity_RenderMeta[] =
{
    &TitleEntity_RenderMeta_1,
    &TitleEntity_RenderMeta_2,
    &TitleEntity_RenderMeta_3,
    ((void*) gConsts::RenderMetaTerminatorPtr)
};

const void** MenuScene_RenderMeta::TitleEntity_RenderMetaPtr = TitleEntity_RenderMeta;
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

static const void* YamadaCopyrightEntity_RenderMeta_1[] =
{
    &YamadaCopyrightEntity_RenderMeta_1_1,
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

static const void* YamadaCopyrightEntity_RenderMeta[] =
{
    &YamadaCopyrightEntity_RenderMeta_1,
    &YamadaCopyrightEntity_RenderMeta_2,
    &YamadaCopyrightEntity_RenderMeta_3,
    ((void*) gConsts::RenderMetaTerminatorPtr)
};

const void** MenuScene_RenderMeta::YamadaCopyrightEntity_RenderMetaPtr = YamadaCopyrightEntity_RenderMeta;
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

static const void* MenuOptionsEntity_RenderMeta_1[] =
{
    &MenuOptionsEntity_RenderMeta_1_1,
    &MenuOptionsEntity_RenderMeta_1_2,
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

static const void* MenuOptionsEntity_RenderMeta[] =
{
    &MenuOptionsEntity_RenderMeta_1,
    &MenuOptionsEntity_RenderMeta_2,
    &MenuOptionsEntity_RenderMeta_3,
    ((void*) gConsts::RenderMetaTerminatorPtr)
};

const void** MenuScene_RenderMeta::MenuOptionsEntity_RenderMetaPtr = MenuOptionsEntity_RenderMeta;
// ------ MenuOptionsEntity RenderMeta END ------
