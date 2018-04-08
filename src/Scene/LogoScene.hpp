#pragma once

#include "GameScene.hpp"
#include <cstdint>

class SaveManager;
class BitmapResourceManager;
class SoundResourceManager;
class StaticPictureEntity;

struct LogoScene_RenderMeta
{
    static const void** LogoEntity_RenderMetaPtr;
};

class LogoScene : public GameScene
{
    public:
        SaveManager* saveManagerPtr;
        BitmapResourceManager* sceneBitmapMgr;
        SoundResourceManager* sceneSoundMgr;
        StaticPictureEntity* logoEntity;
        uint32_t panicButtonsPressedCount;

        LogoScene(SaveManager* aSaveManager);
        virtual ~LogoScene();

        bool CreateEntities();

        virtual int GetNextSceneIDReference() override;
        
        // Not overridden
        // virtual void MakeSureImagesAreReady();
        
        // Not overridden
        // virtual void UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount) override;

        virtual void Update() override;
};