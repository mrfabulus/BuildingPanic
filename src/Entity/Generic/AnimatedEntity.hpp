#pragma once

#include "Entity.hpp"
#include "../../Globals.hpp"
#include <cstdint>

class GameScene;
class Bitmap;

class AnimatedEntity : public Entity
{
    public:
        uint32_t associatedBmpPairObject;

        AnimatedEntity(GameScene* aScene, Bitmap* aBitmap, const RenderMeta* aRenderMeta, uint32_t aBmpPair);
        ~AnimatedEntity();

        virtual void Update() = 0;
        virtual void Render() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources() override;
        virtual bool CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect) override;
        virtual void GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect) override;
};
