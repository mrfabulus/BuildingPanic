#include "Entity/Stage/PlayerWeaponEntity.hpp"
#include "Manager/BitmapResourceManager.hpp"

PlayerWeaponEntity::PlayerWeaponEntity(GameScene* aScene, BitmapResourceManager* aBmpMgr, uint8_t aCharacterChosen)
    : FastEntity(aScene, aBmpMgr->bitmapPtrs[14], &PlayerWeaponEntity_Meta::PlayerWeaponEntity_RenderMeta, aBmpMgr->bitmapCachePtrs[14])
{
    this->extraPosData = nullptr;
    this->feExtraPos3 = nullptr;
    this->byte70 = 0;
    this->byte71 = 0;
    this->characterChosen = aCharacterChosen;

    this->extraPosData = new EntityExtraPositionData3(this);
    this->feExtraPos3 = new FastEntityExtraPositionPair(this, this->extraPosData);

    if (!this->attachedToLayer)
        this->layerIndex = 3;

    this->dword10 = 0;
}

PlayerWeaponEntity::~PlayerWeaponEntity()
{
    this->extraPositionDataBase = nullptr;

    if (this->feExtraPos3 != nullptr)
    {
        delete this->feExtraPos3;
        this->feExtraPos3 = nullptr;
    }

    if (this->extraPosData != nullptr)
    {
        delete this->extraPosData;
        this->extraPosData = nullptr;
    }
}

void PlayerWeaponEntity::Update()
{
    if (!this->attachedToLayer)
        return;

    bool detachSituation1 = (this->byte70 != 0 && this->dword38_assignedZeroFromRenderSetup != 0);

    this->extraPosData->ReassignPositionToEntity();
    this->AssignRenderRectanglesAdvanced();

    bool detachSituation2 = (this->centerX < -32 || this->centerX > 672);

    if (detachSituation1 || detachSituation2)
    {
        this->Detach();
    }
}

// ------ PlayerWeaponEntity RenderMeta START ------
static const uint16_t PlayerWeaponEntity_RenderMeta_1_1[] =
{
    2,
    9,
    4,
    2,
    0,
    2,
    2,
    10,
    4,
    2,
    0,
    1,
};

static const uint16_t PlayerWeaponEntity_RenderMeta_1_2[] =
{
    2,
    16,
    4,
    2,
    0,
    2,
    2,
    17,
    4,
    2,
    0,
    1,
};

static const uint16_t PlayerWeaponEntity_RenderMeta_1_3[] =
{
    2,
    1,
    1,
    1,
    0,
    2,
    2,
    2,
    2,
    1,
    0,
    2,
    2,
    3,
    3,
    1,
    0,
    2,
    2,
    4,
    2,
    1,
    0,
    2,
    2,
    5,
    1,
    1,
    0,
    2,
    2,
    6,
    2,
    1,
    0,
    2,
    2,
    7,
    3,
    1,
    0,
    2,
    2,
    8,
    2,
    1,
    0,
    1,
};

static const uint16_t PlayerWeaponEntity_RenderMeta_1_4[] =
{
    2,
    11,
    5,
    0,
    0,
    2,
    2,
    12,
    6,
    0,
    0,
    2,
    2,
    13,
    7,
    0,
    0,
    2,
    2,
    14,
    8,
    0,
    0,
    2,
    2,
    15,
    8,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t PlayerWeaponEntity_RenderMeta_1_5[] =
{
    2,
    18,
    5,
    0,
    0,
    2,
    2,
    19,
    6,
    0,
    0,
    2,
    2,
    20,
    7,
    0,
    0,
    2,
    2,
    21,
    8,
    0,
    0,
    2,
    2,
    22,
    8,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t* PlayerWeaponEntity_RenderMeta_1[] =
{
    &PlayerWeaponEntity_RenderMeta_1_1[0],
    &PlayerWeaponEntity_RenderMeta_1_2[0],
    &PlayerWeaponEntity_RenderMeta_1_3[0],
    &PlayerWeaponEntity_RenderMeta_1_4[0],
    &PlayerWeaponEntity_RenderMeta_1_5[0],
    0
};

static const MSRect PlayerWeaponEntity_RenderMeta_2[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { 0x50, 0x00, 0x70, 0x28 },
    { 0x00, 0x00, 0x28, 0x28 },
    { 0x00, 0x50, 0x28, 0x70 },
    { 0x00, 0x28, 0x28, 0x50 },
    { 0x50, 0x28, 0x70, 0x50 },
    { 0x28, 0x28, 0x50, 0x50 },
    { 0x28, 0x50, 0x50, 0x70 },
    { 0x28, 0x00, 0x50, 0x28 },
    { 0x00, 0x70, 0x20, 0x80 },
    { 0x00, 0x80, 0x20, 0x90 },
    { 0x40, 0x70, 0x50, 0x80 },
    { 0x50, 0x90, 0x68, 0xa8 },
    { 0x50, 0x50, 0x70, 0x70 },
    { 0x00, 0x90, 0x28, 0xb8 },
    { 0x00, 0xb8, 0x28, 0xe0 },
    { 0x20, 0x70, 0x40, 0x80 },
    { 0x20, 0x80, 0x40, 0x90 },
    { 0x40, 0x80, 0x50, 0x90 },
    { 0x50, 0xa8, 0x68, 0xc0 },
    { 0x50, 0x70, 0x70, 0x90 },
    { 0x28, 0x90, 0x50, 0xb8 },
    { 0x28, 0xb8, 0x50, 0xe0 },
};

static const MSRect PlayerWeaponEntity_RenderMeta_3[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { -16, -20, 0x10, 0x14 },
    { -20, -20, 0x14, 0x14 },
    { -20, -16, 0x14, 0x10 },
    { -16, -8, 0x10, 0x08 },
    { -8, -8, 0x08, 0x08 },
    { -12, -12, 0x0c, 0x0c },
    { -16, -16, 0x10, 0x10 },
    { -20, -20, 0x14, 0x14 },
};

const RenderMeta PlayerWeaponEntity_Meta::PlayerWeaponEntity_RenderMeta =
{
    &PlayerWeaponEntity_RenderMeta_1[0],
    &PlayerWeaponEntity_RenderMeta_2[0],
    &PlayerWeaponEntity_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ PlayerWeaponEntity RenderMeta END ------
