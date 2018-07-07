#include "MenuScene.hpp"
#include "Entity/UI/IntroCutSceneEntity.hpp"
#include "Entity/Generic/StaticPictureEntity.hpp"
#include "Entity/Generic/TileSetEntity.hpp"
#include "Manager/SaveManager.hpp"
#include "Manager/BitmapResourceManager.hpp"
#include "Manager/SoundResourceManager.hpp"
#include "Input/MenuScene_InputProcessor.hpp"
#include <iostream>

uint32_t menuCursorYCoordinates[] =
{
    0x100, 0x120, 0x140, 0x160
};

uint32_t menuOptionCursorCoordinates[] =
{
    0x28, 0x88, 0x28, 0x0A8, 0x28, 0x0C8, 0x28, 0x0E8, 0x28, 0x108,
    0x28, 0x128, 0x28, 0x148, 0x28, 0x168, 0x0F8, 0x188, 0x0F8, 0x1A8
};

uint32_t menuOptionActivationYCoordinates[] =
{
    0x94, 0xB4, 0xD4, 0xF4, 0x114, 0x134, 0x154, 0x174
};

uint32_t menuOptionKeybindCoordinates[] =
{
    0x118, 0x88, 0x118, 0x0A8, 0x118, 0x0C8, 0x118, 0x0E8, 0x118, 0x108,
    0x118, 0x128, 0x118, 0x148, 0x118, 0x168, 0x1E8, 0x88, 0x1E8, 0x0A8,
    0x1E8, 0x0C8, 0x1E8, 0x0E8, 0x1E8, 0x108, 0x1E8, 0x128, 0x1E8, 0x148,
    0x1E8, 0x168
};

MenuScene::MenuScene(SaveManager* aSaveManager)
    : GameScene(gConsts::misc_PaletteDataPtr)
{
    this->saveManager = aSaveManager;
    this->cutScenePhase = 1;
    this->menuChoice = 0;
    this->cutSceneRenderDataPtrIndex = 0;
    this->portraitFlipsLeft = 4;
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

    // Start playing menu midi
    // TODO: Fix music timing (maybe the lack of fade-in and fade-out screws it up?)
    this->sceneSoundMgr->PlayMidi("BPBGM01.MID");
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

    this->fontCharsetEntity = new TileSetEntity(this, this->sceneBitmapMgr->bitmapPtrs[22], &MenuScene_Meta::FontCharset_TileMeta);
    this->fontCharsetEntity->SetLayerIndex(4);

    for (int i = 0; i < 16; i++)
    {
        this->fontGlyphEntities[i] = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[22], &MenuScene_Meta::FontCharset_RenderMeta, 0);
    }
}

int MenuScene::GetNextSceneIDReference()
{
    return (this->menuChoice != 0xFF) + 2;
}

void MenuScene::MakeSureImagesAreReady()
{
    // I don't think we need to implement this for SDL
}

void MenuScene::Update()
{
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
                this->saveManager->saveState.unk2 = ((this->saveManager->saveState.unk2 & 0x10000000) != 0 ? -1 : 10);
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
                    this->CutSceneObject_PortraitFlip(); // eval if fast changes are remaining and go to 5 or 7
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

                // Play sound slot 0
                this->sceneSoundMgr->PlaySoundSlot(0, 320);

                if (this->menuChoice == 2)
                {
                    // Options subscene
                    this->cutScenePhase = 1;
                    this->scenePhaseIndex = 0x13;
                }
                else
                {
                    // Selected play option (either 1 or 2 player mode)
                    // TODO: Set 1Por2P mode in saveManager
                    this->scenePhaseIndex = 2;
                }
            }
            else if ((mask & 0x400040) != 0)
            {
                // UP
                if (this->menuChoice == 0)
                    return;

                // Play sound slot 1
                this->sceneSoundMgr->PlaySoundSlot(1, 320);

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

                // Play sound slot 1
                this->sceneSoundMgr->PlaySoundSlot(1, 320);

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
            // "OPTION" subscene rendering
            switch (this->cutScenePhase)
            {
                case 1:
                    if (!this->fadeIn_active && !this->fadeAway_active)
                    {
                        this->titleEntity->Detach();
                        this->yamadaCopyrightEntity->Detach();
                        this->menuOptionsEntity->Detach();
                        this->optionLabelEntity->Detach();
                        this->menuCursorEntity->Detach();
                        this->cutScenePhase = 2;
                        this->byte959 = 0;
                        this->byte958 = 0;
                        this->fontCharsetEntity->Attach();

                        this->menuCursorEntity->AttachWithPosition(
                            menuOptionCursorCoordinates[2 * this->byte959],
                            menuOptionCursorCoordinates[1 + (2 * this->byte959)], 0);

                        // Setup font glyphs from saved keybindings
                        for (int i = 0; i < 8; i++)
                        {
                            this->fontGlyphEntities[i]->AttachWithPosition(menuOptionKeybindCoordinates[i * 2], menuOptionKeybindCoordinates[(i * 2) + 1], 0);
                            this->fontGlyphEntities[i]->renderDataPtrIndex = this->saveManager->saveState.p1Bindings[i];
                            this->fontGlyphEntities[i]->AssignRenderRectangles(this->saveManager->saveState.p1Bindings[i]);
                        }

                        for (int i = 0; i < 8; i++)
                        {
                            this->fontGlyphEntities[8 + i]->AttachWithPosition(menuOptionKeybindCoordinates[(8 + i) * 2], menuOptionKeybindCoordinates[((8 + i) * 2) + 1], 0);
                            this->fontGlyphEntities[8 + i]->renderDataPtrIndex = this->saveManager->saveState.p2Bindings[i];
                            this->fontGlyphEntities[8 + i]->AssignRenderRectangles(this->saveManager->saveState.p2Bindings[i]);
                        }

                        this->ticksLeftUntilReEval = 32;
                        this->PaletteFadeInStart(1, 32);
                    }
                    break;
                case 2:
                    if (this->ticksLeftUntilReEval <= 0)
                    {
                        if ((mask & 0x10001) != 0)
                        {
                            // ENTER

                            // Play sound slot 0 for 320
                            this->sceneSoundMgr->PlaySoundSlot(0, 320);

                            if (this->byte959 == 9)
                            {
                                // Back to main menu?
                                this->cutScenePhase = 4;
                                this->PaletteFadeAwayStart(1, 32);
                            }
                            else if (this->byte959 == 8)
                            {
                                // Reset to default settings
                                this->saveManager->saveState.LoadDefaultKeyBindings();

                                for (int i = 0; i < 8; i++)
                                {
                                    this->fontGlyphEntities[i]->renderDataPtrIndex = this->saveManager->saveState.p1Bindings[i];
                                    this->fontGlyphEntities[i]->AssignRenderRectangles(this->saveManager->saveState.p1Bindings[i]);
                                }

                                for (int i = 0; i < 8; i++)
                                {
                                    this->fontGlyphEntities[8 + i]->renderDataPtrIndex = this->saveManager->saveState.p2Bindings[i];
                                    this->fontGlyphEntities[8 + i]->AssignRenderRectangles(this->saveManager->saveState.p2Bindings[i]);
                                }
                            }
                            else
                            {
                                this->byte958 = 0;
                                this->cutScenePhase = 3;
                                this->selectCursorEntity->AttachWithPosition(0x118, menuOptionActivationYCoordinates[this->byte959], 0);
                            }
                        }
                        else if ((mask & 0x400040) != 0)
                        {
                            // UP
                            if (this->byte959 != 0)
                            {
                                this->byte959--;

                                // Play sound slot 1 for 320
                                this->sceneSoundMgr->PlaySoundSlot(1, 320);
                            }
                        }
                        else if ((mask & 0x800080) != 0)
                        {
                            // DOWN
                            if (this->byte959 < 9)
                            {
                                this->byte959++;

                                // Play sound slot 1 for 320
                                this->sceneSoundMgr->PlaySoundSlot(1, 320);
                            }
                        }

                        if (this->menuCursorEntity->extraPositionDataBase != nullptr)
                        {
                            this->menuCursorEntity->extraPositionDataBase->dCenterX = menuOptionCursorCoordinates[2 * this->byte959];
                            this->menuCursorEntity->extraPositionDataBase->dCenterY = menuOptionCursorCoordinates[1 + (2 * this->byte959)];
                        }

                        this->menuCursorEntity->centerX = menuOptionCursorCoordinates[2 * this->byte959];
                        this->menuCursorEntity->centerY = menuOptionCursorCoordinates[1 + (2 * this->byte959)];
                    }
                    break;
                case 3:
                    // Handle key setting
                    if ((mask & 0x10001) != 0)
                    {
                        // Play sound slot 0 for 320
                        this->sceneSoundMgr->PlaySoundSlot(0, 320);

                        if (this->byte958 != 0)
                        {
                            this->cutScenePhase = 2;
                            this->selectCursorEntity->Detach();
                        }
                        else
                        {
                            this->byte958 = 1;

                            if (this->selectCursorEntity->extraPositionDataBase != nullptr)
                            {
                                this->selectCursorEntity->extraPositionDataBase->dCenterX = 0x1E8;
                            }

                            this->selectCursorEntity->centerX = 0x1E8;
                        }
                    }
                    else
                    {
                        // TODO: Handle this whole case
                    }
                    break;
                case 4:
                    if (!this->fadeIn_active && !this->fadeAway_active)
                    {
                        this->fontCharsetEntity->Detach();
                        this->menuCursorEntity->Detach();

                        for (int i = 0; i < 16; i++)
                        {
                            this->fontGlyphEntities[i]->Detach();
                        }

                        this->scenePhaseIndex = 0x11;
                    }
                    break;
            }

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

void MenuScene::CutSceneObject_PortraitFlip()
{
    if (this->introCutSceneObject->byte66 != 0)
    {
        this->portraitFlipsLeft--;

        if (this->portraitFlipsLeft != 0)
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

// ------ FontCharset RenderMeta START ------
static const uint16_t FontCharset_RenderMeta_1_1[] =
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

static const uint16_t FontCharset_RenderMeta_1_2[] =
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

static const uint16_t FontCharset_RenderMeta_1_3[] =
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

static const uint16_t FontCharset_RenderMeta_1_4[] =
{
    1,
    4,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_5[] =
{
    1,
    5,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_6[] =
{
    1,
    6,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_7[] =
{
    1,
    7,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_8[] =
{
    1,
    8,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_9[] =
{
    1,
    9,
    1,
    0,
    0,
    0,
    0,
    0
};


static const uint16_t FontCharset_RenderMeta_1_A[] =
{
    1,
    0xA,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_B[] =
{
    1,
    0xB,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_C[] =
{
    1,
    0xC,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_D[] =
{
    1,
    0xD,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_E[] =
{
    1,
    0xE,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_F[] =
{
    1,
    0xF,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_10[] =
{
    1,
    0x10,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_11[] =
{
    1,
    0x11,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_12[] =
{
    1,
    0x12,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_13[] =
{
    1,
    0x13,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_14[] =
{
    1,
    0x14,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_15[] =
{
    1,
    0x15,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_16[] =
{
    1,
    0x16,
    1,
    0,
    0,
    0,
    0,
    0
};


static const uint16_t FontCharset_RenderMeta_1_17[] =
{
    1,
    0x17,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_18[] =
{
    1,
    0x18,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_19[] =
{
    1,
    0x19,
    1,
    0,
    0,
    0,
    0,
    0
};


static const uint16_t FontCharset_RenderMeta_1_1A[] =
{
    1,
    0x1A,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_1B[] =
{
    1,
    0x1B,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_1C[] =
{
    1,
    0x1C,
    1,
    0,
    0,
    0,
    0,
    0
};


static const uint16_t FontCharset_RenderMeta_1_1D[] =
{
    1,
    0x1D,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_1E[] =
{
    1,
    0x1E,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_1F[] =
{
    1,
    0x1F,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_20[] =
{
    1,
    0x20,
    1,
    0,
    0,
    0,
    0,
    0
};


static const uint16_t FontCharset_RenderMeta_1_21[] =
{
    1,
    0x21,
    1,
    0,
    0,
    0,
    0,
    0
};


static const uint16_t FontCharset_RenderMeta_1_22[] =
{
    1,
    0x22,
    1,
    0,
    0,
    0,
    0,
    0
};


static const uint16_t FontCharset_RenderMeta_1_23[] =
{
    1,
    0x23,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_24[] =
{
    1,
    0x24,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_25[] =
{
    1,
    0x25,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_26[] =
{
    1,
    0x26,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_27[] =
{
    1,
    0x27,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_28[] =
{
    1,
    0x28,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_29[] =
{
    1,
    0x29,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_2A[] =
{
    1,
    0x2A,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_2B[] =
{
    1,
    0x2B,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_2C[] =
{
    1,
    0x2C,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_2D[] =
{
    1,
    0x2D,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_2E[] =
{
    1,
    0x2E,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_2F[] =
{
    1,
    0x2F,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_30[] =
{
    1,
    0x30,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_31[] =
{
    1,
    0x31,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_32[] =
{
    1,
    0x32,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t FontCharset_RenderMeta_1_33[] =
{
    1,
    0x33,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t* FontCharset_RenderMeta_1[] =
{
    &FontCharset_RenderMeta_1_1[0],
    &FontCharset_RenderMeta_1_2[0],
    &FontCharset_RenderMeta_1_3[0],
    &FontCharset_RenderMeta_1_4[0],
    &FontCharset_RenderMeta_1_5[0],
    &FontCharset_RenderMeta_1_6[0],
    &FontCharset_RenderMeta_1_7[0],
    &FontCharset_RenderMeta_1_8[0],
    &FontCharset_RenderMeta_1_9[0],
    &FontCharset_RenderMeta_1_A[0],
    &FontCharset_RenderMeta_1_B[0],
    &FontCharset_RenderMeta_1_C[0],
    &FontCharset_RenderMeta_1_D[0],
    &FontCharset_RenderMeta_1_E[0],
    &FontCharset_RenderMeta_1_F[0],
    &FontCharset_RenderMeta_1_10[0],
    &FontCharset_RenderMeta_1_11[0],
    &FontCharset_RenderMeta_1_12[0],
    &FontCharset_RenderMeta_1_13[0],
    &FontCharset_RenderMeta_1_14[0],
    &FontCharset_RenderMeta_1_15[0],
    &FontCharset_RenderMeta_1_16[0],
    &FontCharset_RenderMeta_1_17[0],
    &FontCharset_RenderMeta_1_18[0],
    &FontCharset_RenderMeta_1_19[0],
    &FontCharset_RenderMeta_1_1A[0],
    &FontCharset_RenderMeta_1_1B[0],
    &FontCharset_RenderMeta_1_1C[0],
    &FontCharset_RenderMeta_1_1D[0],
    &FontCharset_RenderMeta_1_1E[0],
    &FontCharset_RenderMeta_1_1F[0],
    &FontCharset_RenderMeta_1_20[0],
    &FontCharset_RenderMeta_1_21[0],
    &FontCharset_RenderMeta_1_22[0],
    &FontCharset_RenderMeta_1_23[0],
    &FontCharset_RenderMeta_1_24[0],
    &FontCharset_RenderMeta_1_25[0],
    &FontCharset_RenderMeta_1_26[0],
    &FontCharset_RenderMeta_1_27[0],
    &FontCharset_RenderMeta_1_28[0],
    &FontCharset_RenderMeta_1_29[0],
    &FontCharset_RenderMeta_1_2A[0],
    &FontCharset_RenderMeta_1_2B[0],
    &FontCharset_RenderMeta_1_2C[0],
    &FontCharset_RenderMeta_1_2D[0],
    &FontCharset_RenderMeta_1_2E[0],
    &FontCharset_RenderMeta_1_2F[0],
    &FontCharset_RenderMeta_1_30[0],
    &FontCharset_RenderMeta_1_31[0],
    &FontCharset_RenderMeta_1_32[0],
    &FontCharset_RenderMeta_1_33[0],
    0,
    0
};

static const MSRect FontCharset_RenderMeta_2[] =
{
    { 0x0, 0x0, 0x1, 0x1 },
    { 0x0, 0x0, 0x10, 0x10 },
    { 0x10, 0x0, 0x20, 0x10 },
    { 0x20, 0x0, 0x30, 0x10 },
    { 0x30, 0x0, 0x40, 0x10 },
    { 0x40, 0x0, 0x50, 0x10 },
    { 0x50, 0x0, 0x60, 0x10 },
    { 0x60, 0x0, 0x70, 0x10 },
    { 0x70, 0x0, 0x80, 0x10 },
    { 0x80, 0x0, 0x90, 0x10 },
    { 0x90, 0x0, 0x0A0, 0x10 },
    { 0x0A0, 0x0, 0x0B0, 0x10 },
    { 0x0B0, 0x0, 0x0C0, 0x10 },
    { 0x0C0, 0x0, 0x0D0, 0x10 },
    { 0x0D0, 0x0, 0x0E0, 0x10 },
    { 0x0E0, 0x0, 0x0F0, 0x10 },
    { 0x0F0, 0x0, 0x100, 0x10 },
    { 0x0, 0x10, 0x10, 0x20 },
    { 0x10, 0x10, 0x20, 0x20 },
    { 0x20, 0x10, 0x30, 0x20 },
    { 0x30, 0x10, 0x40, 0x20 },
    { 0x40, 0x10, 0x50, 0x20 },
    { 0x50, 0x10, 0x60, 0x20 },
    { 0x60, 0x10, 0x70, 0x20 },
    { 0x70, 0x10, 0x80, 0x20 },
    { 0x80, 0x10, 0x90, 0x20 },
    { 0x90, 0x10, 0x0A0, 0x20 },
    { 0x0A0, 0x10, 0x0B0, 0x20 },
    { 0x0B0, 0x10, 0x0C0, 0x20 },
    { 0x0C0, 0x10, 0x0D0, 0x20 },
    { 0x0D0, 0x10, 0x0E0, 0x20 },
    { 0x0E0, 0x10, 0x0F0, 0x20 },
    { 0x0F0, 0x10, 0x100, 0x20 },
    { 0x0, 0x20, 0x10, 0x30 },
    { 0x10, 0x20, 0x20, 0x30 },
    { 0x20, 0x20, 0x30, 0x30 },
    { 0x30, 0x20, 0x40, 0x30 },
    { 0x0, 0x30, 0x10, 0x40 },
    { 0x10, 0x30, 0x20, 0x40 },
    { 0x20, 0x30, 0x30, 0x40 },
    { 0x30, 0x30, 0x40, 0x40 },
    { 0x40, 0x30, 0x50, 0x40 },
    { 0x50, 0x30, 0x60, 0x40 },
    { 0x60, 0x30, 0x70, 0x40 },
    { 0x70, 0x30, 0x80, 0x40 },
    { 0x80, 0x30, 0x90, 0x40 },
    { 0x90, 0x30, 0x0A0, 0x40 },
    { 0x0A0, 0x30, 0x0B0, 0x40 },
    { 0x0B0, 0x30, 0x0C0, 0x40 },
    { 0x0C0, 0x30, 0x0D0, 0x40 },
    { 0x0D0, 0x30, 0x0E0, 0x40 },
    { 0x0E0, 0x30, 0x0F0, 0x40 }
};

static const MSRect FontCharset_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -8, -8, 8, 8 } // lengths to sides (dimensions)
};

const RenderMeta MenuScene_Meta::FontCharset_RenderMeta =
{
    &FontCharset_RenderMeta_1[0],
    &FontCharset_RenderMeta_2[0],
    &FontCharset_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ FontCharset RenderMeta END ------

// ------ FontCharset TileMeta START ------
static const uint16_t FontCharset_TileMeta_1[] =
{
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x14, 0x0E, 0x22, 0x25, 0x0C, 0x18, 0x17, 0x0F, 0x12, 0x10, 0x1E, 0x1B,
    0x0A, 0x1D, 0x12, 0x18, 0x17, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x01, 0x19,
    0x15, 0x0A, 0x22, 0x0E, 0x1B, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x02, 0x19, 0x15, 0x0A, 0x22,
    0x0E, 0x1B, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x13, 0x1E, 0x16, 0x19, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x0A, 0x1D, 0x1D, 0x0A, 0x0C, 0x14, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x0A, 0x1D, 0x1D, 0x0A, 0x0C, 0x14, 0x02, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x0C, 0x1B, 0x0E, 0x0A, 0x1D, 0x0E, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x1E, 0x19, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x0D, 0x18, 0x20, 0x17, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x15, 0x0E, 0x0F, 0x1D, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x1B, 0x12, 0x10, 0x11, 0x1D, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x0D, 0x0E, 0x0F, 0x0A, 0x1E, 0x15, 0x1D, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x0E, 0x21, 0x12, 0x1D, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25,
    0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25, 0x25
};

const TileMeta MenuScene_Meta::FontCharset_TileMeta =
{
    640,
    480,
    16,
    0,
    0,
    0,
    0,
    &FontCharset_TileMeta_1[0],
    &gConsts::TileMeta_StandardRects[0],
    0
};
// ------ FontCharset TileMeta END ------
