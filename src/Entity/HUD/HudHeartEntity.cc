#include "Entity/HUD/HudHeartEntity.hpp"
#include "Scene/GameScene.hpp"
#include "Resource/Bitmap.hpp"

HudHeartEntity::HudHeartEntity(GameScene* aScene, Bitmap* aBitmap)
    : Entity(aScene, aBitmap, &HudHeartEntity_Meta::Default_RenderMeta)
{
    this->heartsLeft = 0;
    this->dword68 = 0;

    if (!this->attachedToLayer)
        this->layerIndex = 4;
    
    this->dword10 = 0;
}

HudHeartEntity::~HudHeartEntity()
{
}

void HudHeartEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    if (this->dword68 != 0)
    {
        this->dword68--;
        this->AssignRenderRectanglesAdvanced();
    }
    else
    {
        this->AssignRenderRectangles(this->heartsLeft);
        this->AssignRenderRectanglesAdvanced();
    }
}

void HudHeartEntity::SetupRenderingInformation()
{
    this->heartsLeft = 8;
    this->dword68 = 0;
    this->ResetRenderRectangleMetadata();
    this->AssignRenderRectangles(this->heartsLeft);
}

// ------ PlaceHolderEntity RenderMeta START ------
static const uint16_t RenderMeta_1_1[] =
{
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_2[] =
{
    1,
    1,
    1,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_3[] =
{
    1,
    2,
    2,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_4[] =
{
    1,
    3,
    3,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_5[] =
{
    1,
    4,
    4,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_6[] =
{
    1,
    5,
    5,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_7[] =
{
    1,
    6,
    6,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_8[] =
{
    1,
    7,
    7,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_9[] =
{
    1,
    8,
    8,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t RenderMeta_1_10[] =
{
    8,
    0,
    0,
    0,
    0,
    2,
    8,
    1,
    1,
    0,
    0,
    1,
};

static const uint16_t RenderMeta_1_11[] =
{
    8,
    1,
    1,
    0,
    0,
    2,
    8,
    2,
    2,
    0,
    0,
    1,
};

static const uint16_t RenderMeta_1_12[] =
{
    8,
    2,
    2,
    0,
    0,
    2,
    8,
    3,
    3,
    0,
    0,
    1,
};

static const uint16_t RenderMeta_1_13[] =
{
    8,
    3,
    3,
    0,
    0,
    2,
    8,
    4,
    4,
    0,
    0,
    1,
};

static const uint16_t RenderMeta_1_14[] =
{
    8,
    4,
    4,
    0,
    0,
    2,
    8,
    5,
    5,
    0,
    0,
    1,
};

static const uint16_t RenderMeta_1_15[] =
{
    8,
    5,
    5,
    0,
    0,
    2,
    8,
    6,
    6,
    0,
    0,
    1,
};

static const uint16_t RenderMeta_1_16[] =
{
    8,
    6,
    6,
    0,
    0,
    2,
    8,
    7,
    7,
    0,
    0,
    1,
};

static const uint16_t RenderMeta_1_17[] =
{
    8,
    7,
    7,
    0,
    0,
    2,
    8,
    8,
    8,
    0,
    0,
    1,
};

static const uint16_t* RenderMeta_1[] =
{
    &RenderMeta_1_1[0],
    &RenderMeta_1_2[0],
    &RenderMeta_1_3[0],
    &RenderMeta_1_4[0],
    &RenderMeta_1_5[0],
    &RenderMeta_1_6[0],
    &RenderMeta_1_7[0],
    &RenderMeta_1_8[0],
    &RenderMeta_1_9[0],
    &RenderMeta_1_10[0],
    &RenderMeta_1_11[0],
    &RenderMeta_1_12[0],
    &RenderMeta_1_13[0],
    &RenderMeta_1_14[0],
    &RenderMeta_1_15[0],
    &RenderMeta_1_16[0],
    &RenderMeta_1_17[0],
    0
};

static const MSRect RenderMeta_2[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { 0x00, 0x00, 0x10, 0x10 },
    { 0x00, 0x00, 0x20, 0x10 },
    { 0x00, 0x00, 0x30, 0x10 },
    { 0x00, 0x00, 0x40, 0x10 },
    { 0x00, 0x00, 0x50, 0x10 },
    { 0x00, 0x00, 0x60, 0x10 },
    { 0x00, 0x00, 0x70, 0x10 },
    { 0x00, 0x00, 0x80, 0x10 },
};

static const MSRect RenderMeta_3[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { 0x00, -8, 0x10, 0x08 },
    { 0x00, -8, 0x20, 0x08 },
    { 0x00, -8, 0x30, 0x08 },
    { 0x00, -8, 0x40, 0x08 },
    { 0x00, -8, 0x50, 0x08 },
    { 0x00, -8, 0x60, 0x08 },
    { 0x00, -8, 0x70, 0x08 },
    { 0x00, -8, 0x80, 0x08 },
};

const RenderMeta HudHeartEntity_Meta::Default_RenderMeta =
{
    &RenderMeta_1[0],
    &RenderMeta_2[0],
    &RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ PlaceHolderEntity RenderMeta END ------
