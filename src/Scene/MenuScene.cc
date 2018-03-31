#include "MenuScene.hpp"
#include "../Entity/UI/IntroCutSceneEntity.hpp"
#include "../Entity/Generic/StaticPictureEntity.hpp"
#include "../Manager/SaveManager.hpp"
#include "../Manager/BitmapResourceManager.hpp"
#include "../Manager/SoundResourceManager.hpp"
#include "../Input/MenuScene_InputProcessor.hpp"
#include <iostream>

MenuScene::MenuScene(SaveManager* aSaveManager)
    : GameScene(/* misc_PaletteData */ nullptr)
{
    this->saveManager = aSaveManager;
    this->cutScenePhase = 1;
    this->menuChoice = 0;
    this->cutSceneRenderDataPtrIndex = 0;
    this->dword8E0 = 4;
    this->inputProcessor = nullptr;
    this->byte958 = 0;
    this->byte959 = 0;
    this->titleEntity = 0;
    this->gap8D8 = 0;

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

void MenuScene::CreateEntities()
{
    this->inputProcessor = new MenuScene_InputProcessor();
    this->titleEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[44], nullptr, 0);
    this->yamadaCopyrightEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[54], nullptr, 0);
    this->menuOptionsEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[53], nullptr, 0);
    this->optionLabelEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[80], nullptr, 0);
    this->menuCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[33], nullptr, 0);
    this->selectCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[37], nullptr, 0);
    this->introCutSceneObject = new IntroCutSceneEntity(this, this->sceneBitmapMgr->bitmapPtrs[71]);

    // TODO: Setup fontCharsetEntity & fontGlyphEntities
    // this->fontCharsetEntity->SetLayerIndex(4);
}

int MenuScene::GetNextSceneIDReference()
{
    return (this->menuChoice != 0xFF) + 2;
}

void MenuScene::F3()
{

}

void MenuScene::F4()
{

}

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
                this->PaletteFadeAwayStart(1, 32);
                this->scenePhaseIndex = 0x11;
            }

            switch (this->cutScenePhase)
            {
                case 2:
                    this->InitCutSceneObject();
                    break;
                case 3:
                    this->CutSceneObject_F2();
                    break;
                case 4:
                    this->CutSceneObject_F3();
                    break;
                case 5:
                    this->CutSceneObject_F5();
                    break;
                case 6:
                    this->CutSceneObject_F6();
                    break;
                case 7:
                    this->CutSceneObject_F2();
                    break;
                case 8:
                    this->InitMainMenu();
                    break;
                default:
                    break;
            }

            break;
        case 0x11:
            // // cutscene skip (I think ??)
            if (!this->fadeIn_active && !this->fadeAway_active)
            {
                // IntroCutScene_4146A0(this->introCutSceneObject, 0);
                this->scenePhaseIndex = 0x10;
                this->cutScenePhase = 8;
                this->ticksLeftUntilReEval = 45;
                this->PaletteFadeInStart(1, 32);
            }
            break;
        case 0x12:
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
    this->introCutSceneObject->AssignRenderRectangles(this->cutSceneRenderDataPtrIndex);
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
        // TODO: cutSceneObject->something()
        this->cutScenePhase++;
    }
}

void MenuScene::CutSceneObject_F4()
{
    if (this->introCutSceneObject->byte66)
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
        this->ticksLeftUntilReEval = 1800;
        this->scenePhaseIndex = 0x12;
    }
}
