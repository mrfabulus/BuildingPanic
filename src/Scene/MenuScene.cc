#include "MenuScene.hpp"

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
    // TODO: Create BitmapResourceManager
    // TODO: Create SoundResourceManager
    this->CreateEntities();

    this->ticksLeftUntilReEval = 90;
    // TODO: start playing menu midi
}