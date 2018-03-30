#pragma once

#include "GameScene.hpp"
#include "../Manager/SaveManager.hpp"
#include "../Manager/BitmapResourceManager.hpp"
#include "../Manager/SoundResourceManager.hpp"
#include "../Entity/StaticPictureEntity.hpp"
#include "../Input/LogoScene_InputProcessor.hpp"

class LogoScene : public GameScene
{
    public:
        SaveManager* saveManagerPtr;
        BitmapResourceManager* sceneBitmapMgr;
        SoundResourceManager* sceneSoundMgr;
        StaticPictureEntity* logoEntity;
        int panicButtonsPressedCount;

        LogoScene(SaveManager* aSaveManager);

        bool CreateEntities()
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

        int GetNextSceneIDReference() override
        {
            return 1; // reference to MenuScene
        }
        
        virtual void F3();
        
        void F4() override
        {

        }

        void Tick() override
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
};