#include "WallEntity.hpp"
#include "../Generic/StaticPictureEntity.hpp"

WallEntity::WallEntity(GameScene* aScene, Bitmap* aBitmap, uint32_t aCenterX, uint32_t aCenterY)
    : Entity(aScene, aBitmap, nullptr)
{
    this->byte64 = 0;
    this->byte65 = 0;
    this->byte66 = 0;
    this->dword68 = 0;
    this->dword6C = 0;
    this->extraPositionData = 0;
    this->wallImageEntity = nullptr;

    if (!this->attachedToLayer)
    {
        this->layerIndex = 1;
    }

    this->centerY = aCenterY;
    this->centerX = aCenterX;

    this->AssignRenderRectangles(0);
    this->wallImageEntity = new StaticPictureEntity(aScene, aBitmap, nullptr, 1);
    this->wallImageEntity->dword10 = 0;
    this->wallImageEntity->renderDataPtrIndex = 30;
    this->wallImageEntity->AssignRenderRectangles(30);
    this->wallImageEntity->coordinateLikeThingie = 1;
    this->wallImageEntity->SetLayerIndex(1);
}

WallEntity::~WallEntity()
{
    if (this->extraPositionData != nullptr)
    {
        delete this->extraPositionData;
        this->extraPositionData = nullptr;
    }

    if (this->wallImageEntity != nullptr)
    {
        delete this->wallImageEntity;
        this->wallImageEntity = nullptr;
    }
}

void WallEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    if (this->byte66 != 0 && this->dword38_assignedZeroFromRenderSetup != 0)
    {
        this->byte66 = 0;
    }

    this->extraPositionData->ReassignPositionToEntity();
    this->AssignRenderRectanglesAdvanced();
}

void WallEntity::SetupRenderingInformation()
{
    this->byte65 = 0;
    this->dword68 = 1;
    this->extraPositionData = new EntityExtraPositionData(this);
    this->extraPositionDataBase = this->extraPositionData;

    /*
    v4 = (char)this->byte65;
    Entity_AssignRenderRectangles(&this->base, aRenderDataPtrIndex[v4 + 3 * (char)this->byte64]);
    */

    this->byte66 = 1;
}

void WallEntity::ReleaseResources()
{
    this->extraPositionDataBase = nullptr;

    if (this->extraPositionData != nullptr)
    {
        delete this->extraPositionData;
        this->extraPositionData = nullptr;
    }
}
