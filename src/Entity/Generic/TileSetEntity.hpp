#pragma once

#include <cstdint>

#include "Globals.hpp"
#include "SDL2_Interface.hpp"

#include "Entity/Generic/Entity.hpp"
#include "Entity/Generic/TileSetEntity_base.hpp"

class GameScene;
class Bitmap;

class TileSetEntity : public TileSetEntity_base
{
    public:
        SDL_Surface* composedSurface;
        TileMeta* tileMetadata;
        uint32_t horizontalTileCount;
        uint32_t verticalTileCount;
        uint32_t width;
        uint32_t height;
        EntityExtraPositionData* extraPositionData;

        TileSetEntity(GameScene* aScene, Bitmap* aBitmap, const TileMeta* aTileMetadataPtr);
        ~TileSetEntity();

        void Attach();
        void Detach();

        void StaticBlt(MSRect* aSrcRect, MSRect* aDstRect, SDL_Surface* aSurface);
        void BltToComposed(uint16_t rectIndex, MSRect* dstRect);
        void GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect);
        bool CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect);
        void AttachWithPosition(int32_t aX, int32_t aY);

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRendering() override;
        virtual void ReleaseResources() override;
        virtual void MakeSureImageIsReady() override;
        virtual void SetupSurface();
        virtual void RenderTiles();
};