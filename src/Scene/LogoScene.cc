#include "LogoScene.hpp"

LogoScene::LogoScene(SaveManager* aSaveManager)
    : GameScene(/* misc_PaletteData */ nullptr)
{
    this->saveManagerPtr = aSaveManager;
    this->panicButtonsPressedCount = 0;
    
    if (this->CreateEntities())
    {
        this->logoEntity->AttachWithPosition(320, 240, 0);
        this->ticksLeftUntilReEval = 300; // show for 5 seconds ( 60 frames / sec ); then start fadeaway into MenuScene
        this->scenePhaseIndex = 1;

        this->PaletteFadeInStart(1, 32);
    }
    else
    {
        this->init_OK = 0;
    }
}

void LogoScene::F3()
{

}
