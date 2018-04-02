#include "CharacterChoiceScene.hpp"
#include "../Entity/Generic/StaticPictureEntity.hpp"
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
    // TODO: oh boi
}

bool CharacterChoiceScene::CreateEntities()
{
    this->inputProcessor = new MenuHandler_InputProcessor();
    this->sceneBitmapMgr = new BitmapResourceManager(3, nullptr, 0);
    this->sceneSoundMgr = new SoundResourceManager(3);

    // TODO: Create stageSelectTiles

    this->selectTextEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[46], nullptr, 0);
    this->selectSubtextsEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[49], nullptr, 0);
    this->selectionCursorEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[67], nullptr, 0);
    this->unknownStageSymbol1 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->unknownStageSymbol2 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->unknownStageSymbol3 = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[68], nullptr, 0);
    this->player1PortraitEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[72], nullptr, 0);
    this->player2PortraitEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[72], nullptr, 0);

    return true;
}

void CharacterChoiceScene::Init()
{
    // TODO: Initialize stageSelectTiles
    this->selectTextEntity->AttachWithPosition(320, 64, 0);

    this->player1PortraitEntity->AttachWithPosition(0xB0, 240, 0);
    this->player1PortraitEntity->renderDataPtrIndex = 0;
    this->player1PortraitEntity->AssignRenderRectangles(0);

    this->player2PortraitEntity->AttachWithPosition(0xD0, 240, 0);
    this->player2PortraitEntity->renderDataPtrIndex = 1;
    this->player2PortraitEntity->AssignRenderRectangles(1);

    this->ticksLeftUntilReEval = 60;
    this->PaletteFadeInStart(1, 32);
    // TODO: start bpbgm02.mid
}
