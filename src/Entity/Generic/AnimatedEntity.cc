#include "AnimatedEntity.hpp"
#include "../../Resource/Bitmap.hpp"

AnimatedEntity::AnimatedEntity(GameScene* aScene, Bitmap* aBitmap, const RenderMeta* aRenderMeta, uint32_t aBmpPair)
    : Entity(aScene, aBitmap, aRenderMeta)
{
    this->associatedBmpPairObject = aBmpPair;
}

AnimatedEntity::~AnimatedEntity()
{
}

void AnimatedEntity::Render()
{
    if (!this->attachedToLayer)
        return;

    if (this->associatedBmpPairObject == 0)
    {
        Entity::Render();
        return;
    }

    MSRect srcRect;
    MSRect dstRect;

    this->GetRenderRectangles(&srcRect, &dstRect);
    bool renderOK = this->CheckRenderBoundaries(&srcRect, &dstRect);

    if (!renderOK)
        return;

    if (this->entityFacingLeft)
    {
        // TODO: render pair
    }
    else
    {
        this->entityImageBmp->Render(&srcRect, &dstRect);
    }
}

void AnimatedEntity::SetupRenderingInformation()
{
    /*
    v1 = this->associatedBmpPairObject;
    if ( v1 )
    {
        if ( !v1->dwordC )
            BitmapPairObject_4050D0(v1);
        result = v1->dwordC + 1;
        v1->dwordC = result;
    }
    */
}

void AnimatedEntity::ReleaseResources()
{
    /*
    v1 = (Bitmap *)this->associatedBmpPairObject;
    if ( v1 )
        result = Bitmap_decRefCount(v1);
    */
}

bool AnimatedEntity::CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect)
{
    // TODO: Implement 00401990
    return true;
}

void AnimatedEntity::GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect)
{
    if (this->associatedBmpPairObject == 0)
    {
        Entity::GetRenderRectangles(aSrcRect, aDstRect);
        return;
    }

    // TODO: Implement more 004018C9
}
