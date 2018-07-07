#include "Entity/Generic/AnimatedEntity.hpp"
#include "Resource/Bitmap.hpp"
#include "Resource/BitmapCacheSurface.hpp"

AnimatedEntity::AnimatedEntity(GameScene* aScene, Bitmap* aBitmap, const RenderMeta* aRenderMeta, BitmapCacheSurface* aCacheSurface)
    : Entity(aScene, aBitmap, aRenderMeta)
{
    this->cacheSurface = aCacheSurface;
}

AnimatedEntity::~AnimatedEntity()
{
}

void AnimatedEntity::Render()
{
    if (!this->attachedToLayer)
        return;

    // printf("AnimatedEntity::Render 1\n");

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

    printf("AnimatedEntity::Render 2\n");
    MSRect srcRect;
    MSRect dstRect;

    this->GetRenderRectangles(&srcRect, &dstRect);
    bool renderOK = this->CheckRenderBoundaries(&srcRect, &dstRect);

    if (!renderOK)
        return;

    if (this->renderCacheSurface)
    {
        printf("AnimatedEntity::Render 3\n");
        this->cacheSurface->Render(&srcRect, &dstRect);
    }
    else
    {
        printf("AnimatedEntity::Render 4\n");
        this->entityImageBmp->Render(&srcRect, &dstRect);
    }
}

void AnimatedEntity::SetupRenderingInformation()
{
    if (this->cacheSurface != nullptr)
    {
        if (this->cacheSurface->refCount == 0)
        {
            this->cacheSurface->SetupSurface();
        }

        this->cacheSurface->refCount++;
    }
}

void AnimatedEntity::ReleaseResources()
{
    if (this->cacheSurface != nullptr)
    {
        this->cacheSurface->DecRefCount();
    }
}

bool AnimatedEntity::CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect)
{
    // TODO: Implement 00401990
    return true;
}

void AnimatedEntity::GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect)
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
