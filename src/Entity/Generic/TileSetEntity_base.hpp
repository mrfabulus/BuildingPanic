#pragma once

#include "Entity.hpp"
#include <cstdint>

class GameScene;
class Bitmap;
class EntityExtraPositionData;

// Sorta like an "EntityMinimal" class
class TileSetEntity_base : public GameObject
{
    public:
        GameScene* scenePtr;
        Bitmap* bitmap;
        EntityExtraPositionData* extraPositionDataBase;
        bool attachedToLayer;

        TileSetEntity_base(GameScene* aScene, Bitmap* aBitmap);
        virtual ~TileSetEntity_base();

        // New entries in the VTable
        virtual void SetupRendering();
        virtual void ReleaseResources();
        virtual void MakeSureImageIsReady();
};
