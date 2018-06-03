#pragma once

#include <cstdint>
#include "Entity/Generic/Entity.hpp"

class StaticPictureEntity;
class GameScene;
class Bitmap;

struct WallEntity_Meta
{
    static const RenderMeta WallEntity_RenderMeta;
};

enum WallOwner : uint8_t
{
    WallOwner_Doka = 0,
    WallOwner_Tobi = 1,
    WallOwner_Garcia = 2
};

class WallEntity : public Entity
{
    public:
        uint8_t byte64;
        uint8_t byte65;
        uint8_t byte66;
        uint32_t dword68;
        uint32_t dword6C;
        EntityExtraPositionData* extraPositionData;
        StaticPictureEntity* wallImageEntity;

        WallEntity(GameScene* aScene, Bitmap* aBitmap, uint32_t aCenterX, uint32_t aCenterY);
        virtual ~WallEntity();

        void PreSet(WallOwner buildStage);

        virtual void Update() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources() override;
};
