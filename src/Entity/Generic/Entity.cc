#include "Entity.hpp"
#include "../../Scene/GameScene.hpp"
#include "../../Resource/Bitmap.hpp"
#include <iostream>

EntityExtraPositionData::EntityExtraPositionData(Entity* aEntity)
{
    this->entityPtr = aEntity;
    this->dCenterX = aEntity->centerX;
    this->dCenterY = aEntity->centerY;
    this->coordinateLikeThingie = aEntity->dword1C_coordinateLikeThingie;
}

Entity::Entity(GameScene* aScene, Bitmap* aBitmap, void* dataPtrs)
    : Entity_base()
{
    this->scene = aScene;
    this->entityImageBmp = aBitmap;
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

Entity::~Entity()
{
}

void Entity::ResetRenderRectangleMetadata()
{
    this->renderDataPtrIndex = 0xFFFF;
    this->field_42 = 0;
    this->firstWordFromRenderDataPtr1 = 0xFFFF;
    this->dword38_assignedZeroFromRenderSetup = 0;
}

void Entity::AssignRenderRectangles(uint16_t aRenderDataPtrIndex)
{
    if (this->renderDataPtrIndex != aRenderDataPtrIndex)
    {
        // TODO: Implement this fucked up logic for real...
        // TODO: Also, don't forget this shit is memleaking below

        MSRect* phantomSrc = (MSRect*) malloc(sizeof(MSRect));

        phantomSrc->left = 0;
        phantomSrc->top = 0;
        phantomSrc->right = 0x138;
        phantomSrc->bottom = 0x20;

        this->srcRectPtr = phantomSrc;

        MSRect* phantomDim = (MSRect*) malloc(sizeof(MSRect));

        phantomDim->left = -156;
        phantomDim->top = -16;
        phantomDim->right = 156;
        phantomDim->bottom = 16;

        this->dimensionRectPtr = phantomDim;
    }
}

void Entity::AssignRenderRectanglesAdvanced()
{
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

void Entity::Render()
{
    if (!this->attachedToLayer)
        return;

    MSRect srcRect;
    MSRect dstRect;

    this->GetRenderRectangles(&srcRect, &dstRect);
    bool renderOK = this->CheckRenderBoundaries(&srcRect, &dstRect);

    if (!renderOK)
        return;

    this->entityImageBmp->Render(&srcRect, &dstRect);
}

bool Entity::AttachWithPosition(int32_t aX, int32_t aY, uint16_t AttachedRenderDataIndex)
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
        this->entityImageBmp->decRefCount();
        this->attachedToLayer = false;
    }
}

bool Entity::CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect)
{
    return true;
}

bool Entity::GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect)
{
    aSrcRect->left = this->srcRectPtr->left;
    aSrcRect->top = this->srcRectPtr->top;
    aSrcRect->right = this->srcRectPtr->right;
    aSrcRect->bottom = this->srcRectPtr->bottom;

    // TODO: Take facing into account, etc
    aDstRect->left = dimensionRectPtr->left + this->centerX;
    aDstRect->right = dimensionRectPtr->right + this->centerX;

    aDstRect->top = this->centerY + this->dimensionRectPtr->top;
    aDstRect->bottom = this->centerY + this->dimensionRectPtr->bottom;
}

void Entity::Update()
{
}

void Entity::SetupRenderingInformation()
{
}

void Entity::ReleaseResources()
{
}
