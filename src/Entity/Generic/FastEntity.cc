#include "Entity/Generic/FastEntity.hpp"
#include "Resource/Bitmap.hpp"
#include "Resource/OffscreenSurface.hpp"

FastEntity::FastEntity(GameScene* aScene, Bitmap* aBitmap, const RenderMeta* aRenderMeta, OffscreenSurface* aCacheSurface)
    : Entity(aScene, aBitmap, aRenderMeta)
{
    this->cacheSurface = aCacheSurface;
}

FastEntity::~FastEntity()
{
}

void FastEntity::Render()
{
    if (!this->attachedToLayer)
        return;

    // printf("FastEntity::Render 1\n");

    if (this->cacheSurface == nullptr)
    {
        MSRect srcRect;
        MSRect dstRect;
        this->GetRenderRectangles(&srcRect, &dstRect);
        
        SDL_Rect SDL_srcRect = srcRect.ToSDLRect();
        SDL_Rect SDL_dstRect = dstRect.ToSDLRect();

        printf("Rendering %s\n", this->entityImageBmp->resourceName.c_str());
        printf("src %d %d %d %d\n", SDL_srcRect.x, SDL_srcRect.y, SDL_srcRect.w, SDL_srcRect.h);
        printf("dst %d %d %d %d\n", SDL_dstRect.x, SDL_dstRect.y, SDL_dstRect.w, SDL_dstRect.h);

        Entity::Render();
        return;
    }

    printf("FastEntity::Render 2\n");

    MSRect srcRect;
    MSRect dstRect;

    this->GetRenderRectangles(&srcRect, &dstRect);

    if (!this->CheckRenderBoundaries(&srcRect, &dstRect))
        return;

    if (this->renderCacheSurface)
    {
        printf("FastEntity::Render 3\n");
        this->cacheSurface->Render(&srcRect, &dstRect);
    }
    else
    {
        printf("FastEntity::Render 4\n");
        this->entityImageBmp->Render(&srcRect, &dstRect);
    }
}

void FastEntity::SetupRenderingInformation()
{
    if (this->cacheSurface != nullptr)
    {
        if (this->cacheSurface->refCount == 0)
        {
            // Cache is still new, need to render on the surface first
            this->cacheSurface->SetupSurface();
        }

        this->cacheSurface->refCount++;
    }
}

void FastEntity::ReleaseResources()
{
    if (this->cacheSurface != nullptr)
    {
        this->cacheSurface->DecRefCount();
    }
}

bool FastEntity::CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect)
{
    // TODO: Implement 00401990
    return true;
}

void FastEntity::GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect)
{
    if (this->cacheSurface == nullptr)
    {
        Entity::GetRenderRectangles(aSrcRect, aDstRect);
        return;
    }

    aSrcRect->top = this->srcRectPtr->top;
    aSrcRect->bottom = this->srcRectPtr->bottom;

    if (this->renderCacheSurface != 0)
    {
        aSrcRect->left = this->cacheSurface->bitmapPtr->SDL_surface->w - this->srcRectPtr->right;
        aSrcRect->right = this->cacheSurface->bitmapPtr->SDL_surface->w - this->srcRectPtr->left;

        aDstRect->left = this->centerX - this->dimensionRectPtr->right;
        aDstRect->right = this->centerX - this->dimensionRectPtr->left;
    }
    else
    {
        aSrcRect->left = this->srcRectPtr->left;
        aSrcRect->right = this->srcRectPtr->right;
        
        aDstRect->left = this->centerX + this->dimensionRectPtr->left;
        aDstRect->right = this->centerX + this->dimensionRectPtr->right;
    }

    aDstRect->top = this->centerY + this->dimensionRectPtr->top;
    aDstRect->bottom = this->centerY + this->dimensionRectPtr->bottom;
}
