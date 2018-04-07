#pragma once

#include "Entity.hpp"
#include <cstdint>

class GameScene;
class Bitmap;

class StaticPictureEntity : public Entity
{
    public:
        int8_t byte64_lastArg;
        uint16_t renderDataPtrIndex;
        EntityExtraPositionData* extraPositionData2;

        StaticPictureEntity (GameScene* aScene, Bitmap* aBitmap, void* dataPtrs, char a5);
        ~StaticPictureEntity();

        virtual void SetupRenderingInformation() override;
};
