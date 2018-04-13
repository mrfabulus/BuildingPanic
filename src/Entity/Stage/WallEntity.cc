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
    this->extraPositionData = nullptr;
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

    uint32_t indexLinker[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0x1B, 0x1C, 0x1D };
    uint16_t renderCfgIndex = indexLinker[this->byte65 + 3 * this->byte64];
    this->AssignRenderRectangles(renderCfgIndex);

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

// ------ WallEntity RenderMeta START ------
static const uint16_t WallEntity_RenderMeta_1_1[] =
{
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0
};

static const uint16_t* WallEntity_RenderMeta_1[] =
{
    &WallEntity_RenderMeta_1_1[0],
    0
};

static const MSRect WallEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0xA0, 0xA0 },
    { 0xA0, 0, 0x140, 0xA0 },
    { 0x140, 0, 0x1E0, 0xA0 }
};

static const MSRect WallEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -80, -80, 80, 80 } // lengths to sides (dimensions)
};

const RenderMeta WallEntity_Meta::WallEntity_RenderMeta =
{
    &WallEntity_RenderMeta_1[0],
    &WallEntity_RenderMeta_2[0],
    &WallEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ WallEntity RenderMeta END ------
