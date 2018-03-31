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
    this->sceneBitmapMgr = new BitmapResourceManager(1, nullptr, 0);
    this->sceneSoundMgr = new SoundResourceManager(1);
    this->CreateEntities();

    this->ticksLeftUntilReEval = 90;
    // TODO: start playing menu midi
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

    // TODO: Further initialization
    this->introCutSceneObject = nullptr;

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

    switch (this->scenePhaseIndex)
    {
        case 1:
            break;
    }
}
