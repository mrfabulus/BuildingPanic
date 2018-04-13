#include "Entity.hpp"
#include "../../Scene/GameScene.hpp"
#include "../../Resource/Bitmap.hpp"
#include <iostream>
#include <stdlib.h>

EntityExtraPositionData::EntityExtraPositionData(GameObject* aEntity)
{
    this->entityPtr = aEntity;
    this->dCenterX = aEntity->centerX;
    this->dCenterY = aEntity->centerY;
    this->coordinateLikeThingie = aEntity->coordinateLikeThingie;
}

EntityExtraPositionData::~EntityExtraPositionData()
{
}

void EntityExtraPositionData::ReassignPositionToEntity()
{
    this->entityPtr->centerX = (int32_t) this->dCenterX;
    this->entityPtr->centerY = (int32_t) this->dCenterY;
}

Entity::Entity(GameScene* aScene, Bitmap* aBitmap, const RenderMeta* dataPtrs)
    : GameObject()
{
    this->scene = aScene;
    this->entityImageBmp = aBitmap;
    this->extraPositionDataBase = nullptr;
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

// TODO: Find a cleaner way to implement this
void Entity::AssignRenderRectangles(uint16_t aRenderDataPtrIndex)
{
    if (this->renderDataPtrIndex != aRenderDataPtrIndex)
    {
        this->renderDataPtrIndex = aRenderDataPtrIndex;
        std::cout << "AssignRenderRectangles for index " << aRenderDataPtrIndex << std::endl;

        if (this->dataPtrs == nullptr)
            return;

        const uint16_t** cfg = this->dataPtrs->configurations;
        cfg += aRenderDataPtrIndex;

        this->dataPtr1 = * ((uint16_t**) cfg);
        this->firstWordFromRenderDataPtr1 = this->dataPtr1[0];

        this->srcRectPtr = (MSRect*) (this->dataPtrs->srcRectangles + this->dataPtr1[1]);
        this->dimensionRectPtr = (MSRect*) (this->dataPtrs->dimRectangles + this->dataPtr1[2]);

        this->dword38_assignedZeroFromRenderSetup = 0;

        this->lastDataPtrRectanglePtr = (MSRect*) (this->dataPtrs->terminator + this->dataPtr1[3]);
    }
}

void Entity::AssignRenderRectanglesAdvanced()
{
    // TODO: implement @ 004016F0
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

void Entity::Update()
{
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

    if (this->dataPtrs == nullptr)
    {
        std::cout << "WARNING, missing render meta information" << std::endl;
        return false;
    }

    double doubleX = (double) aX;
    double doubleY = (double) aY;

    if (this->extraPositionDataBase)
    {
        this->extraPositionDataBase->dCenterX = doubleX;
        this->extraPositionDataBase->dCenterY = doubleY;
    }

    this->centerX = aX;
    this->centerY = aY;
    this->AttachedRenderDataIndex = AttachedRenderDataIndex;

    this->entityImageBmp->incRefCount();
    this->SetupRenderingInformation();
    this->scene->AttachGameObjectToLayer(this);
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

    if (this->extraPositionDataBase)
    {
        this->extraPositionDataBase->dCenterX = doubleX;
        this->extraPositionDataBase->dCenterY = doubleY;
        this->extraPositionDataBase->coordinateLikeThingie = unk;
    }

    this->centerX = aX;
    this->centerY = aY;
    this->coordinateLikeThingie = unk;

    this->AttachedRenderDataIndex = AttachedRenderDataIndex;

    this->entityImageBmp->incRefCount();
    this->SetupRenderingInformation();
    this->scene->AttachGameObjectToLayer(this);
    this->attachedToLayer = true;

    return true;
}

void Entity::Detach()
{
    if (this->attachedToLayer)
    {
        this->ReleaseResources();
        this->scene->DetachGameObjectFromLayer(this);
        this->entityImageBmp->decRefCount();
        this->attachedToLayer = false;
    }
}

bool Entity::CheckRenderBoundaries(MSRect* aSrcRect, MSRect* aDstRect)
{
    return true;
}

void Entity::GetRenderRectangles(MSRect* aSrcRect, MSRect* aDstRect)
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

void Entity::SetupRenderingInformation()
{
}

void Entity::ReleaseResources()
{
}
