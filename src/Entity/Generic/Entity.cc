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

EntityExtraPositionData3::EntityExtraPositionData3(GameObject* aEntity)
    : EntityExtraPositionData(aEntity)
{
    this->double1 = 0;
    this->double2 = 0;
    this->byte38 = 1;
    this->byte39 = 1;
}

EntityExtraPositionData3::~EntityExtraPositionData3()
{
}

void EntityExtraPositionData3::ReassignPositionToEntity()
{
    this->ReassignPositionXYToEntity(this->double1, this->double2);
}

void EntityExtraPositionData3::ReassignPositionXYToEntity(double aX, double aY)
{
    double newX = (this->byte38 * aX) + this->dCenterX;
    double newY = (this->byte39 * aY) + this->dCenterY;

    this->dCenterX = newX;
    this->entityPtr->centerX = newX;
    this->dCenterY = newY;
    this->entityPtr->centerY = newY;
}

Entity::Entity(GameScene* aScene, Bitmap* aBitmap, const RenderMeta* aRenderMeta)
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
    this->renderMeta = aRenderMeta;
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
    this->renderConfigIndex = 0xFFFF;
    this->field_42 = 0;
    this->firstWordFromRenderConfig = 0xFFFF;
    this->dword38_assignedZeroFromRenderSetup = 0;
}

void Entity::AssignRenderRectangles(uint16_t aRenderConfigIndex)
{
    // Check if the new configuration is different than the existing one
    if (this->renderConfigIndex != aRenderConfigIndex)
    {
        this->renderConfigIndex = aRenderConfigIndex;

        if (this->renderMeta == nullptr)
            return;

        // Get the appropriate configuration pointer from the list
        const uint16_t** cfg = this->renderMeta->configurations;
        cfg += renderConfigIndex;

        this->renderConfiguration = * ((uint16_t**) cfg);
        this->firstWordFromRenderConfig = this->renderConfiguration[0];

        this->srcRectPtr = (MSRect*) (this->renderMeta->srcRectangles + this->renderConfiguration[1]);
        this->dimensionRectPtr = (MSRect*) (this->renderMeta->dimRectangles + this->renderConfiguration[2]);

        this->dword38_assignedZeroFromRenderSetup = 0;

        this->lastDataPtrRectanglePtr = (MSRect*) (this->renderMeta->terminator + this->renderConfiguration[3]);
    }
}

bool Entity::AssignRenderRectanglesAdvanced()
{
    bool result = false;

    if (this->firstWordFromRenderConfig != 0)
    {
        this->dword38_assignedZeroFromRenderSetup = 0;
        this->firstWordFromRenderConfig--;
    }
    else
    {
        uint16_t value = this->renderConfiguration[5];

        if (value != 0)
        {
            if (value == 2)
            {
                this->field_42++;
                this->dword38_assignedZeroFromRenderSetup = 0;
            }
            else
            {
                this->field_42 = 0;
                this->dword38_assignedZeroFromRenderSetup = 1;
                result = true;
            }

            const uint16_t** cfg = this->renderMeta->configurations;
            cfg += renderConfigIndex;

            this->renderConfiguration = * ((uint16_t**) cfg);
            this->renderConfiguration += (3 * this->field_42);

            this->firstWordFromRenderConfig = this->renderConfiguration[0] - 1;

            this->srcRectPtr = (MSRect*) (this->renderMeta->srcRectangles + this->renderConfiguration[1]);
            this->dimensionRectPtr = (MSRect*) (this->renderMeta->dimRectangles + this->renderConfiguration[2]);
            this->lastDataPtrRectanglePtr = (MSRect*) (this->renderMeta->terminator + this->renderConfiguration[3]);
        }
        else
        {
            this->dword38_assignedZeroFromRenderSetup = 1;
            result = true;
        }
    }

    return result;
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

    if (this->renderMeta == nullptr)
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
