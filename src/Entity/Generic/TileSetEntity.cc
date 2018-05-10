#include <iostream>
#include "Entity/Generic/TileSetEntity.hpp"
#include "Resource/Bitmap.hpp"
#include "Scene/GameScene.hpp"

TileSetEntity::TileSetEntity(GameScene* aScene, Bitmap* aBitmap, const TileMeta* aTileMetadataPtr)
    : TileSetEntity_base(aScene, aBitmap)
{
    this->composedSurface = nullptr;
    this->tileMetadata = (TileMeta*) aTileMetadataPtr;
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

    this->centerX = aTileMetadataPtr->centerX;
    this->centerY = aTileMetadataPtr->centerY;

    this->horizontalTileCount = aTileMetadataPtr->width / aTileMetadataPtr->tileSize;
    this->verticalTileCount = aTileMetadataPtr->height / aTileMetadataPtr->tileSize;

    uint32_t finalWidth = aTileMetadataPtr->width;

    if (finalWidth > 640)
        finalWidth = 640;

    this->width = finalWidth;

    uint32_t finalHeight = aTileMetadataPtr->height;

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

    this->bitmap->IncRefCount();
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
        this->bitmap->DecRefCount();
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
    aSrcRect->left = this->tileMetadata->unk1;
    aSrcRect->top = this->tileMetadata->unk2;
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
    this->composedSurface = gSys.CreateSurface(this->tileMetadata->width, this->tileMetadata->height);

    if (this->composedSurface == nullptr)
        return;

    // Set transparent color key to black
    SDL_SetColorKey(this->composedSurface, SDL_TRUE, SDL_MapRGB(this->composedSurface->format, 0, 0, 0));
}

void TileSetEntity::RenderTiles()
{
    if (this->tileMetadata->srcRectIndexes == nullptr)
        return;

    if (this->verticalTileCount == 0)
        return;

    // Process the tiles line-by-line (1 horizontal line at a time)
    for (uint32_t verticalProgress = 0; verticalProgress < this->verticalTileCount; verticalProgress++)
        for (uint32_t horizontalProgress = 0; horizontalProgress < this->horizontalTileCount; horizontalProgress++)
        {
            uint32_t tileIndex = (this->horizontalTileCount * verticalProgress) + horizontalProgress;
            uint16_t srcRectIndex = this->tileMetadata->srcRectIndexes[tileIndex];

            MSRect rect;
            rect.top = this->tileMetadata->tileSize * verticalProgress;
            rect.left = this->tileMetadata->tileSize * horizontalProgress;
            rect.bottom = this->tileMetadata->tileSize + rect.top;
            rect.right = this->tileMetadata->tileSize + rect.left;

            MSRect* srcRectMS = (MSRect*) &(this->tileMetadata->rectangles[srcRectIndex]);

            SDL_Rect srcRect = srcRectMS->ToSDLRect();
            SDL_Rect dstRect = rect.ToSDLRect();

            SDL_BlitSurface(this->bitmap->SDL_surface, &srcRect, this->composedSurface, &dstRect);
        }
}
