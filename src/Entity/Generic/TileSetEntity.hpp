#pragma once

#include <cstdint>
#include "../../SDL2_Interface.hpp"
#include "../../Globals.hpp"
#include "TileSetEntity_base.hpp"
#include "Entity.hpp"

class GameScene;
class Bitmap;

class TileSetEntity : public TileSetEntity_base
{
    public:
        SDL_Surface* composedSurface;
        uint32_t* tileMetadata;
        uint32_t horizontalTileCount;
        uint32_t verticalTileCount;
        uint32_t width;
        uint32_t height;
        EntityExtraPositionData* extraPositionData;

        TileSetEntity(GameScene* aScene, Bitmap* aBitmap, uint32_t* aTileMetadataPtr);
        ~TileSetEntity();

        void Attach();
        void Blt(MSRect* aSrcRect, MSRect* aDstRect, SDL_Surface* aSurface);
        void GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect);
        bool CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect);

        virtual void Update() override;
        virtual void Render() override;
        virtual void SetupRendering() override;
        virtual void ReleaseResources() override;
        virtual void MakeSureImageIsReady() override;
        virtual void SetupSurface();
        virtual void RenderTiles();
};