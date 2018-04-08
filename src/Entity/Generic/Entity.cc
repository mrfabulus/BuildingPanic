#include "Entity.hpp"
#include "../../Scene/GameScene.hpp"
#include "../../Resource/Bitmap.hpp"
#include <iostream>
#include <stdlib.h>

EntityExtraPositionData::EntityExtraPositionData(Entity* aEntity)
{
    this->entityPtr = aEntity;
    this->dCenterX = aEntity->centerX;
    this->dCenterY = aEntity->centerY;
    this->coordinateLikeThingie = aEntity->dword1C_coordinateLikeThingie;
}

Entity::Entity(GameScene* aScene, Bitmap* aBitmap, const uint32_t** dataPtrs)
    : GameObject()
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

// TODO: Find a cleaner way to implement this
void Entity::AssignRenderRectangles(uint16_t aRenderDataPtrIndex)
{
    if (this->renderDataPtrIndex != aRenderDataPtrIndex)
    {
        this->renderDataPtrIndex = aRenderDataPtrIndex;
        std::cout << "AssignRenderRectangles for index " << aRenderDataPtrIndex << std::endl;

        if (this->dataPtrs == nullptr)
            return;

        uint32_t multiplier = 0;

        // Since the structure that is used is pretty messed up, pointer calculations have to be made accordingly
        #ifdef WIN32
        multiplier = 1;
        #else
        multiplier = 2;
        #endif

        std::cout << "dataPtrs[0] = " << this->dataPtrs[0] << std::endl;

        for (uint32_t i = 0; i < aRenderDataPtrIndex + 1; i++)
        {
            std::cout << "Reading from " << (this->dataPtrs[0] + i * multiplier) << std::endl;

            #ifdef WIN32
            uint32_t* debugP = ((uint32_t*)(this->dataPtrs[0] + i * multiplier));
            #else
            uint64_t* debugP = ((uint64_t*) (this->dataPtrs[0] + i * multiplier));
            #endif

            std::cout << "dataPtrs[0][" << i << "] = 0x" << std::hex << *debugP << std::endl;
        }

        uint16_t* p = (uint16_t*) (* ((uint64_t*) (this->dataPtrs[0] + aRenderDataPtrIndex * multiplier)));
        std::cout << "Calculated p " << p << std::endl;

        this->dataPtr1 = p;
        this->firstWordFromRenderDataPtr1 = p[0];

        MSRect* srcRects = (MSRect*) this->dataPtrs[1];
        this->srcRectPtr = srcRects + p[1];

        MSRect* dimensionRects = (MSRect*) this->dataPtrs[2];
        this->dimensionRectPtr = dimensionRects + p[2];

        this->dword38_assignedZeroFromRenderSetup = 0;

        MSRect* unkRects = (MSRect*) this->dataPtrs[3];
        this->lastDataPtrRectanglePtr = unkRects + p[3];
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
