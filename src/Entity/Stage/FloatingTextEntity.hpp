#pragma once

#include "../Generic/Entity.hpp"
#include <cstdint>

class FloatingTextEntity : public Entity
{
    public:
        EntityExtraPositionData3* extraPositionData;
        uint32_t dword68;

        FloatingTextEntity(GameScene* aScene, Bitmap* aBitmap);
        virtual ~FloatingTextEntity();

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources();
};
