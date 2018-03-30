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

        bool CreateEntities();

        int GetNextSceneIDReference() override;
        
        virtual void F3();
        
        virtual void F4() override;

        virtual void Update() override;
};