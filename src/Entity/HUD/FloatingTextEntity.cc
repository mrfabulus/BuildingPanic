#include "Resource/Bitmap.hpp"
#include "Entity/HUD/FloatingTextEntity.hpp"

// TODO: Render meta
FloatingTextEntity::FloatingTextEntity(GameScene* aScene, Bitmap* aBitmap)
    : Entity(aScene, aBitmap, nullptr)
{
    this->extraPositionData = nullptr;
    this->dword68 = 0;

    this->extraPositionData = new EntityExtraPositionData3(this);
    this->extraPositionDataBase = this->extraPositionData;
    this->extraPositionData->double2 = 1;
    this->extraPositionData->byte39 = -1;

    if (!this->attachedToLayer)
    {
        this->layerIndex = 3;
    }

    this->coordinateLikeThingie = 20;
    this->dword10 = 0;
}

FloatingTextEntity::~FloatingTextEntity()
{
    this->extraPositionDataBase = nullptr;

    if (this->extraPositionData != nullptr)
    {
        delete this->extraPositionData;
        this->extraPositionData = nullptr;
    }
}

void FloatingTextEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    this->extraPositionData->ReassignPositionToEntity();
    this->dword68++;

    if (this->AssignRenderRectanglesAdvanced())
    {
        this->Detach();
    }
}

void FloatingTextEntity::Render()
{
    if (!this->attachedToLayer)
        return;

    MSRect srcRect;
    MSRect dstRect;

    this->GetRenderRectangles(&srcRect, &dstRect);

    // Don't ask me why...
    uint32_t dword_457B10[] = { 4, 4, 3, 3, 2, 2, 1, 1, 0, 0, 1, 1, 2, 2, 3, 3 };
    uint32_t v3 = dword_457B10[this->dword68 & 0xF];

    dstRect.top += v3;
    dstRect.bottom -= v3;

    bool renderOK = this->CheckRenderBoundaries(&srcRect, &dstRect);

    if (!renderOK)
        return;

    this->entityImageBmp->Render(&srcRect, &dstRect);
}

void FloatingTextEntity::SetupRenderingInformation()
{
    this->dword68 = 0;
    this->ResetRenderRectangleMetadata();
    this->AssignRenderRectangles(0);
}

void FloatingTextEntity::ReleaseResources()
{
}
