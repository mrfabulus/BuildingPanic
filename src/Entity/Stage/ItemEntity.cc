#include "ItemEntity.hpp"

ItemEntity::ItemEntity(GameScene* aScene, Bitmap* aBitmap)
    : Entity(aScene, aBitmap, &ItemEntity_Meta::ItemEntity_RenderMeta)
{
    this->extraPositionData = nullptr;
    this->byte68 = 0;
    this->word6A = 0;
    this->dword6C = 0;
    this->coordinateLikeThingie = 20;
}

ItemEntity::~ItemEntity()
{
    if (this->extraPositionData != nullptr)
    {
        delete this->extraPositionData;
        this->extraPositionData = nullptr;
    }
}

void ItemEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    this->dword6C--;

    if (this->dword6C != 0)
    {
        this->extraPositionData->ReassignPositionToEntity();
        if (this->dword10 == 0)
        {
            // ??
        }

        // ??
        this->AssignRenderRectanglesAdvanced();
    }
    else
    {
        this->Detach();
    }
}

void ItemEntity::Render()
{
    if (this->dword6C >= 0x12C || (this->dword6C % 2 == 0))
    {
        Entity::Render();
    }
}

void ItemEntity::SetupRenderingInformation()
{
    this->extraPositionData = new EntityExtraPositionData3(this);
    this->extraPositionDataBase = this->extraPositionData;
    this->ResetRenderRectangleMetadata();
}

void ItemEntity::ReleaseResources()
{
    this->extraPositionDataBase = nullptr;

    if (this->extraPositionData != nullptr)
    {
        delete this->extraPositionData;
        this->extraPositionData = nullptr;
    }
}


// ------ ItemEntity RenderMeta START ------
// TODO: dump actual numbers (its a lot...)
static const uint16_t ItemEntity_RenderMeta_1_1[] =
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

static const uint16_t* ItemEntity_RenderMeta_1[] =
{
    &ItemEntity_RenderMeta_1_1[0],
    0
};

static const MSRect ItemEntity_RenderMeta_2[] =
{
    { 0, 0, 1, 1 },
    { 0, 0, 0xA0, 0xA0 },
    { 0xA0, 0, 0x140, 0xA0 },
    { 0x140, 0, 0x1E0, 0xA0 }
};

static const MSRect ItemEntity_RenderMeta_3[] =
{
    { 0, 0, 1, 1 },
    { -80, -80, 80, 80 } // lengths to sides (dimensions)
};

const RenderMeta ItemEntity_Meta::ItemEntity_RenderMeta =
{
    &ItemEntity_RenderMeta_1[0],
    &ItemEntity_RenderMeta_2[0],
    &ItemEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ ItemEntity RenderMeta END ------
