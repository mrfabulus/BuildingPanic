#pragma once

#include "GameScene.hpp"
#include "../Manager/SaveManager.hpp"
#include "../Manager/BitmapResourceManager.hpp"
#include "../Entity/StaticPictureEntity.hpp"

class LogoScene : public GameScene
{
    public:
        SaveManager* saveManagerPtr;
        BitmapResourceManager* sceneBitmapMgr;
        // SoundResourceManager* sceneSoundMgr;
        void* sceneSoundMgr;
        StaticPictureEntity* logoEntity;
        int panicButtonsPressedCount;

        LogoScene(SaveManager* aSaveManager)
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

        bool CreateEntities()
        {
            // TODO: Create Input Processor
            // TODO: Create BitmapResourceMgr
            // TODO: Create SoundResourceMgr
            this->logoEntity = new StaticPictureEntity(this, nullptr, nullptr, 0);

            if (this->logoEntity != nullptr)
                return true;
            else
            {
                // bpanic_ShowError_wrapper(8001, 4, memAllocFailStr);
                return false;
            }
        }
};