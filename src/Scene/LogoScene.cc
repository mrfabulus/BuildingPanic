#include "LogoScene.hpp"
#include "Entity/Generic/StaticPictureEntity.hpp"
#include "Manager/BitmapResourceManager.hpp"
#include "Manager/SoundResourceManager.hpp"
#include "Manager/SaveManager.hpp"
#include "Input/LogoScene_InputProcessor.hpp"
#include "Globals.hpp"

LogoScene::LogoScene(SaveManager* aSaveManager)
    : GameScene(gConsts::misc_PaletteDataPtr)
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

LogoScene::~LogoScene()
{
    if (this->logoEntity != nullptr)
    {
        delete this->logoEntity;
        this->logoEntity = nullptr;
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

bool LogoScene::CreateEntities()
{
    this->inputProcessor = new LogoScene_InputProcessor();
    this->sceneBitmapMgr = new BitmapResourceManager(0, nullptr, 0);
    this->sceneSoundMgr = new SoundResourceManager(0);

    // LOGO_BMP for the loading screen
    this->logoEntity = new StaticPictureEntity(this, this->sceneBitmapMgr->bitmapPtrs[17], &LogoScene_Meta::LogoEntity_RenderMeta, 0);

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

/*
void LogoScene::MakeSureImagesAreReady()
{

}

void LogoScene::UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount)
{

}
*/

void LogoScene::Update()
{
    switch (this->scenePhaseIndex)
    {
        case 1:
            if (this->ticksLeftUntilReEval > 0)
            {
                // Check if the cheat has been activated before
                if ((this->saveManagerPtr->saveState.unk2 & 0x10000000) == 0)
                {
                    if (this->panicButtonsPressedCount >= 5)
                    {
                        this->saveManagerPtr->saveState.nextStageIndex = 4;
                        this->saveManagerPtr->saveState.unk2 = 0xFFFFFFFF;

                        // Play "SELECT" sound
                        this->sceneSoundMgr->PlaySoundSlot(0, 320);
                        std::cout << "PANIC cheat activated" << std::endl;
                    }
                    else
                    {
                        uint32_t buttonOrder[] = { 1, 2, 4, 8, 16 };

                        if (buttonOrder[this->panicButtonsPressedCount] & this->inputProcessor->newButtonPressesMask)
                        {
                            std::cout << "PANIC increase: " << this->panicButtonsPressedCount << std::endl;
                            this->panicButtonsPressedCount++;
                        }
                    }
                }
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

// ------ LogoEntity RenderMeta START ------
static const uint16_t LogoEntity_RenderMeta_1_1[] =
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

static const uint16_t* LogoEntity_RenderMeta_1[] =
{
    &LogoEntity_RenderMeta_1_1[0],
    0
};

static const MSRect LogoEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 312, 32 } // src rectangle
};

static const MSRect LogoEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -156, -16, 156, 16 } // lengths to sides (dimensions)
};

const RenderMeta LogoScene_Meta::LogoEntity_RenderMeta =
{
    &LogoEntity_RenderMeta_1[0],
    &LogoEntity_RenderMeta_2[0],
    &LogoEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};

// ------ LogoEntity RenderMeta END ------
