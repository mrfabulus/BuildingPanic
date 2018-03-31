#include "LogoScene.hpp"

LogoScene::LogoScene(SaveManager* aSaveManager)
    : GameScene(/* misc_PaletteData */ nullptr)
{
    this->saveManagerPtr = aSaveManager;
    this->panicButtonsPressedCount = 0;
    
    if (this->CreateEntities())
    {
        this->logoEntity->AttachWithPosition(320, 240, 0);
        this->ticksLeftUntilReEval = /* 30; */  300; // show for 5 seconds ( 60 frames / sec ); then start fadeaway into MenuScene
        this->scenePhaseIndex = 1;

        this->PaletteFadeInStart(1, 32);
    }
    else
    {
        this->init_OK = false;
    }
}

bool LogoScene::CreateEntities()
{
    this->inputProcessor = new LogoScene_InputProcessor();
    this->sceneBitmapMgr = new BitmapResourceManager(0, nullptr, 0);
    this->sceneSoundMgr = new SoundResourceManager(0);

    // LOGO_BMP for the loading screen
    this->logoEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[17], nullptr, 0);

    if (this->logoEntity != nullptr)
        return true;
    else
    {
        // bpanic_ShowError_wrapper(8001, 4, memAllocFailStr);
        return false;
    }
}

int LogoScene::GetNextSceneIDReference()
{
    return 1; // reference to MenuScene
}

void LogoScene::F3()
{

}

void LogoScene::UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount)
{

}

void LogoScene::Update()
{
    switch (this->scenePhaseIndex)
    {
        case 1:
            if (this->ticksLeftUntilReEval > 0)
            {
                // TODO: Check InputProcessor for PANIC cheat code and add logic
            }
            else
            {
                this->PaletteFadeAwayStart(1, 32);
                this->scenePhaseIndex = 2;
            }

            break;
        case 2:
            // Once the fadeaway effect finishes, we leave this scene and start the menu's cutscene
            this->SetFinishedIfFadesDone();
            break;
    }
}