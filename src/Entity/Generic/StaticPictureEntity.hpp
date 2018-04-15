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
        EntityExtraPositionData* extraPositionData;

        StaticPictureEntity (GameScene* aScene, Bitmap* aBitmap, const RenderMeta* dataPtrs, char a5);
        ~StaticPictureEntity();

        virtual void Update() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources() override;
};
