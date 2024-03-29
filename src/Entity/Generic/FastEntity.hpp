#pragma once

#include <cstdint>
#include "Globals.hpp"
#include "Entity/Generic/Entity.hpp"

class GameScene;
class Bitmap;
class OffscreenSurface;

class FastEntity : public Entity
{
    public:
        OffscreenSurface* cacheSurface;

        FastEntity(GameScene* aScene, Bitmap* aBitmap, const RenderMeta* aRenderMeta, OffscreenSurface* aCacheSurface);
        virtual ~FastEntity();

        virtual void Update() = 0;
        virtual void Render() override;
        virtual void SetupRenderingInformation() override;
        virtual void ReleaseResources() override;
        virtual bool CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect) override;
        virtual void GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect) override;
};
