#include "TileSetEntity.hpp"
#include "../../Resource/Bitmap.hpp"
#include "../../Scene/GameScene.hpp"
#include <iostream>

TileSetEntity::TileSetEntity(GameScene* aScene, Bitmap* aBitmap, const uint32_t* aTileMetadataPtr)
    : TileSetEntity_base(aScene, aBitmap)
{
    this->composedSurface = nullptr;
    this->tileMetadata = (uint32_t*) aTileMetadataPtr;
    this->horizontalTileCount = 0;
    this->verticalTileCount = 0;
    this->width = 0;
    this->height = 0;
    this->extraPositionData = nullptr;

    if (aTileMetadataPtr == nullptr)
    {
        std::cout << "Warning: missing tilemetadata for an entity" << std::endl;
        return;
    }

    this->centerX = aTileMetadataPtr[3];
    this->centerY = aTileMetadataPtr[4];

    this->horizontalTileCount = aTileMetadataPtr[0] / aTileMetadataPtr[2];
    this->verticalTileCount = aTileMetadataPtr[1] / aTileMetadataPtr[2];

    uint32_t finalWidth = aTileMetadataPtr[0];

    if (finalWidth > 640)
        finalWidth = 640;

    this->width = finalWidth;

    uint32_t finalHeight = aTileMetadataPtr[1];

    if (finalHeight > 480)
        finalHeight = 480;

    this->height = finalHeight;

    if (!this->attachedToLayer)
        this->layerIndex = 0;
}

TileSetEntity::~TileSetEntity()
{
}

void TileSetEntity::Attach()
{

    if (this->attachedToLayer)
        return;

    this->bitmap->incRefCount();
    this->SetupRendering();
    this->scenePtr->AttachGameObjectToLayer(this);
    this->attachedToLayer = true;
}

void TileSetEntity::Detach()
{
    if (this->attachedToLayer)
    {
        this->ReleaseResources();
        this->scenePtr->DetachGameObjectFromLayer(this);
        this->bitmap->decRefCount();
        this->attachedToLayer = false;
    }
}

void TileSetEntity::Blt(MSRect* aSrcRect, MSRect* aDstRect, SDL_Surface* aSurface)
{
    // Manual conversion from MS style rects into SDL style
    SDL_Rect SDL_srcRect = aSrcRect->ToSDLRect();
    SDL_Rect SDL_dstRect = aDstRect->ToSDLRect();

    // SDL_RenderCopy(gSys.GetRenderer(), this->SDL_texture, &SDL_srcRect, &SDL_dstRect);
    SDL_BlitSurface(aSurface, &SDL_srcRect, gSys.GetMainSurface(), &SDL_dstRect);
}

void TileSetEntity::GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect)
{
    aSrcRect->left = this->tileMetadata[5];
    aSrcRect->top = this->tileMetadata[6];
    aSrcRect->right = aSrcRect->left + this->width;
    aSrcRect->bottom = aSrcRect->top + this->height;

    aDstRect->left = this->centerX;
    aDstRect->top = this->centerY;
    aDstRect->right = this->centerX + width;
    aDstRect->bottom = this->centerY + height;
}

bool TileSetEntity::CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect)
{
    return true;
}

void TileSetEntity::Update()
{
    if (this->extraPositionData != nullptr)
    {
        this->extraPositionData->ReassignPositionToEntity();
    }
}

void TileSetEntity::Render()
{
    if (!this->attachedToLayer)
        return;

    if (this->tileMetadata == nullptr)
    {
        return;
    }

    MSRect srcRect;
    MSRect dstRect;

    this->GetRenderRectangles(&srcRect, &dstRect);
    bool renderOK = this->CheckRenderBoundaries(&srcRect, &dstRect);

    if (!renderOK)
        return;

    std::cout << "TileSetEntity::Blt incoming" << std::endl;
    this->Blt(&srcRect, &dstRect, this->composedSurface);
}


void TileSetEntity::SetupRendering()
{
    if (this->tileMetadata == nullptr)
    {
        std::cout << "Warning: missing tilemetadata for an entity, stopped setting up rendering" << std::endl;
        return;
    }

    this->SetupSurface();
    this->RenderTiles();

    this->extraPositionData = new EntityExtraPositionData(this);
    this->extraPositionDataBase = nullptr;
}

void TileSetEntity::ReleaseResources()
{
    if (this->composedSurface != nullptr)
    {
        SDL_FreeSurface(this->composedSurface);
        this->composedSurface = nullptr;
    }

    this->extraPositionDataBase = nullptr;

    if (this->extraPositionData != nullptr)
    {
        delete this->extraPositionData;
        this->extraPositionData = nullptr;
    }
}

void TileSetEntity::MakeSureImageIsReady()
{
}

void TileSetEntity::SetupSurface()
{
    this->composedSurface = gSys.CreateSurface(this->tileMetadata[0], this->tileMetadata[1]);

    if (this->composedSurface == nullptr)
        return;

    // Set transparent color key to black
    SDL_SetColorKey(this->composedSurface, SDL_TRUE, SDL_MapRGB(this->composedSurface->format, 0, 0, 0));
}

void TileSetEntity::RenderTiles()
{
    std::cout << "TileSetEnity::RenderTiles 1" << std::endl;

/*
    if (this->tileMetadata[7] == 0)
        return;
        */

    std::cout << "TileSetEnity::RenderTiles 2" << std::endl;

    if (this->verticalTileCount <= 0)
        return;

    std::cout << "TileSetEnity::RenderTiles 3" << std::endl;

    // TODO: Complicated logic >:(
    uint32_t verticalProgress = 0; // v2
    uint32_t horizontalProgress; // v3
    uint32_t v4;

    while ( 1 )
    {
        horizontalProgress = this->horizontalTileCount;
        v4 = 0;
        
        if ( horizontalProgress > 0 )
            break;
        
        LABEL_6:
        if ( ++verticalProgress >= this->verticalTileCount )
        {
            std::cout << "TileSetEnity::RenderTiles finished (?)" << std::endl;
            return;
        }
    }

    while ( 1 )
    {
        uint32_t* cRef = this->tileMetadata;
        uint16_t v6 = *(uint16_t *)(cRef[7] + 2 * (v4 + horizontalProgress * verticalProgress));
        MSRect rect;
        rect.top = cRef[2] * verticalProgress;
        rect.left = cRef[2] * v4;
        rect.bottom = cRef[2] + rect.top;
        rect.right = cRef[2] + rect.left;

        MSRect* srcRectMS = (*((MSRect**) this->tileMetadata[8])) + v6;

        SDL_Rect srcRect = srcRectMS->ToSDLRect();
        SDL_Rect dstRect = rect.ToSDLRect();
        
        std::cout << "TileSetEnity::RenderTiles blitting for " << verticalProgress << " " << horizontalProgress << std::endl;
        SDL_BlitSurface(this->bitmap->SDL_surface, &srcRect, this->composedSurface, &dstRect);
        
        horizontalProgress = this->horizontalTileCount;

        if ( ++v4 >= horizontalProgress )
            goto LABEL_6;
    }
}
