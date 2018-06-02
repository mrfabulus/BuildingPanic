#pragma once

#include "Entity/Generic/Entity.hpp"
#include <cstdint>

class GameScene;
class Bitmap;


struct HudHeartEntity_Meta
{
    static const RenderMeta Default_RenderMeta;
};

class HudHeartEntity : public Entity
{
    public:
        uint16_t heartsLeft;
        uint32_t dword68;

        HudHeartEntity(GameScene* aScene, Bitmap* aBitmap);
        virtual ~HudHeartEntity();

        virtual void Update() override;
        virtual void SetupRenderingInformation() override;
};
