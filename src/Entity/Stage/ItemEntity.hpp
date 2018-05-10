#pragma once

#include <cstdint>
#include "Entity/Generic/Entity.hpp"

class GameScene;
class Bitmap;

struct ItemEntity_Meta
{
    static const RenderMeta ItemEntity_RenderMeta;
};

class ItemEntity : public Entity
{
    public:
        EntityExtraPositionData3* extraPositionData;
        uint8_t byte68;
        uint16_t word6A;
        uint32_t dword6C;

        ItemEntity(GameScene* aScene, Bitmap* aBitmap);
        virtual ~ItemEntity();

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources() override;
};
