#pragma once

#include "GameScene.hpp"
#include "../Manager/SaveManager.hpp"
#include "../Manager/BitmapResourceManager.hpp"
#include "../Manager/SoundResourceManager.hpp"
#include "../Entity/Generic/StaticPictureEntity.hpp"
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
        ~LogoScene();

        bool CreateEntities();

        int GetNextSceneIDReference() override;
        
        // Not overridden
        // virtual void F3();
        
        // Not overridden
        // virtual void UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount) override;

        virtual void Update() override;
};