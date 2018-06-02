#pragma once

#include "Entity/Generic/Entity.hpp"
#include <cstdint>

class GameScene;
class Bitmap;

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
