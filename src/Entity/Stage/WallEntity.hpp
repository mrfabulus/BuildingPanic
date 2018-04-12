#pragma once

#include "../Generic/Entity.hpp"
#include <cstdint>

class StaticPictureEntity;
class GameScene;
class Bitmap;

class WallEntity : public Entity
{
    public:
        uint8_t byte64;
        uint8_t byte65;
        uint8_t byte66;
        uint32_t dword68;
        uint32_t dword6C;
        EntityExtraPositionData* dword70;
        StaticPictureEntity* wallImageEntity;

        WallEntity(GameScene* aScene, Bitmap* aBitmap, uint32_t aCenterX, uint32_t aCenterY);
        virtual ~WallEntity();

        virtual void Update() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources() override;
};
