#include "Entity.hpp"

Entity::Entity(GameScene* aScene, void* aBitmap, void* dataPtrs)
    : Entity_base()
{
    this->scene = aScene;
    this->entityImageBmp = (Bitmap*) aBitmap;
    this->extraPositionData = 0;
    this->attachedToLayer = 0;
    this->entityFacingLeft = 0;
    this->dword34 = 0;
    this->dword38_assignedZeroFromRenderSetup = 0;
    this->dword3C = 0;
    this->dataPtrs = dataPtrs;
    this->word5C = 0;
    this->AttachedRenderDataIndex = 0;
    this->dword60 = 0;

    if ( !aBitmap )
    {
        // bpanic_ShowError_wrapper(600, 1, &surfaceUninitializedErrorStr);// Surface is not initialized.
    }

    this->ResetRenderRectangleMetadata();
}

void Entity::SetLayerIndex(uint16_t aLayerIndex)
{
    if (!this->attachedToLayer)
    {
        if (aLayerIndex >= 5)
        {
            this->layerIndex = 1;
        }
        else
        {
            this->layerIndex = aLayerIndex;
        }
    }
}

// TODO: Implement
bool Entity::Render()
{
    if (!this->attachedToLayer)
        return true;

    // this->GetRenderRectangles();
    // this->CheckRenderBoundaries();

    if (this->entityFacingLeft)
    {

    }
    else
    {

    }
}

bool Entity::AttachWithPosition(int aX, int aY, uint16_t AttachedRenderDataIndex)
{
    if (this->attachedToLayer)
        return false;

    double doubleX = (double) aX;
    double doubleY = (double) aY;

    if (this->extraPositionData)
    {
        this->extraPositionData->dCenterX = doubleX;
        this->extraPositionData->dCenterY = doubleY;
    }

    this->centerX = aX;
    this->centerY = aY;
    this->AttachedRenderDataIndex = AttachedRenderDataIndex;

    this->entityImageBmp->incRefCount();
    this->SetupRenderingInformation();
    this->scene->AttachEntityToLayer(this);
    this->attachedToLayer = true;

    return true;
}

bool Entity::AttachWithPosition2(int32_t aX, int32_t aY, int32_t unk, uint16_t AttachedRenderDataIndex)
{
    if (this->attachedToLayer)
        return false;

    double doubleX = (double) aX;
    double doubleY = (double) aY;
    double dUnk = (double) unk;

    if (this->extraPositionData)
    {
        this->extraPositionData->dCenterX = doubleX;
        this->extraPositionData->dCenterY = doubleY;
        this->extraPositionData->coordinateLikeThingie = unk;
    }

    this->centerX = aX;
    this->centerY = aY;
    this->dword1C_coordinateLikeThingie = unk;

    this->AttachedRenderDataIndex = AttachedRenderDataIndex;

    this->entityImageBmp->incRefCount();
    this->SetupRenderingInformation();
    this->scene->AttachEntityToLayer(this);
    this->attachedToLayer = true;

    return true;
}

bool Entity::Detach()
{
    if (this->attachedToLayer)
    {
        this->ReleaseResources();
        this->scene->DetachEntityFromLayer(this);
        this->entityImageBmp->Detach();
        this->attachedToLayer = false;
    }
}

void Entity::ResetRenderRectangleMetadata()
{
    this->renderDataPtrIndex = 0xFFFF;
    this->field_42 = 0;
    this->firstWordFromRenderDataPtr1 = 0xFFFF;
    this->dword38_assignedZeroFromRenderSetup = 0;
}
