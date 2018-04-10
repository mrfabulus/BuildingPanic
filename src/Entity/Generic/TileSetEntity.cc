#include "TileSetEntity.hpp"
#include "../../Resource/Bitmap.hpp"
#include "../../Scene/GameScene.hpp"

TileSetEntity::TileSetEntity(GameScene* aScene, Bitmap* aBitmap, uint32_t* aTileMetadataPtr)
    : TileSetEntity_base(aScene, aBitmap)
{
    this->composedSurface = nullptr;
    this->tileMetadata = aTileMetadataPtr;
    this->horizontalTileCount = 0;
    this->verticalTileCount = 0;
    this->width = 0;
    this->height = 0;
    this->extraPositionData = nullptr;

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
    if (this->tileMetadata[7] == 0)
        return;

    if (this->verticalTileCount <= 0)
        return;

    // TODO: Complicated logic >:(

    /*
    while ( 1 )
    {
        v3 = this->horizontalTileCount;
        v4 = 0;
        
        if ( v3 > 0 )
            break;
        
        LABEL_6:
        if ( ++v2 >= this->verticalTileCount )
            return 1;
    }

    while ( 1 )
    {
        v5 = this->tileMetadata;
        v6 = *(_WORD *)(v5[7] + 2 * (v4 + v3 * v2));
        rect.top = v5[2] * v2;
        rect.left = v5[2] * v4;
        rect.bottom = v5[2] + rect.top;
        rect.right = v5[2] + rect.left;
        
        if ( !oss_blt(this, v6, &rect) )
            return 0;
        
        v3 = this->horizontalTileCount;
        if ( ++v4 >= v3 )
            goto LABEL_6;
    }
    */
}
