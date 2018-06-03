#include "Entity/Stage/PlayerEntity.hpp"
#include "Entity/Generic/StaticPictureEntity.hpp"
#include "Manager/BitmapResourceManager.hpp"
#include "Manager/SoundResourceManager.hpp"
#include "Scene/Stages/Ingame_Stage_Scene.hpp"

// TODO: Pass render meta based on character chosen
PlayerEntity::PlayerEntity(Ingame_Stage_Scene* aScene, BitmapResourceManager* aBmpMgr, int aCharacterChosen, SoundResourceManager* aSndMgr, int a6)
    : AnimatedEntity(aScene, aBmpMgr->bitmapPtrs[aCharacterChosen], &PlayerEntity_Meta::Doka_RenderMeta, aBmpMgr->bitmapCachePtrs[aCharacterChosen])
{
    this->double80 = 0;
    this->dword88 = 0;
    this->byte68 = aCharacterChosen;
    this->byte69 = 0;
    this->byte6A = 0;
    this->byte6B = 0;
    this->byte6C = 0;
    this->byte6D = 0;
    this->unsigned6E = 3;
    this->dword70 = 0;
    this->dword74 = 0;
    this->dword78 = 0;
    this->dword7C = a6;
    this->dword8C = 0;
    this->dword90 = 0;
    this->extraPositionData = 0;
    this->dword98 = 0;
    this->dword9C = nullptr;
    this->piyoBmp = 0;
    this->dwordA4 = 0;
    this->hitBmp = 0;
    this->sndMgr = aSndMgr;
    this->dwordBC = 0;

    this->piyoBmp = new StaticPictureEntity(aScene, aBmpMgr->bitmapPtrs[18], nullptr, 0);
    this->piyoBmp->dword10 = 0;

    this->hitBmp = new StaticPictureEntity(aScene, aBmpMgr->bitmapPtrs[20], nullptr, 0);
    this->hitBmp->SetLayerIndex(3);
    this->hitBmp->coordinateLikeThingie = 10;
    this->hitBmp->dword10 = 0;

    for (int i = 3; i > 0; i--)
    {
        // TODO: Create something??
    }

    this->extraPositionData = new EntityExtraPositionData3(this);

    // this->dword98 = new ???

    this->coordinateLikeThingie = 100 * this->unsigned6E + 20;
    this->AssignRenderRectangles(0);
}

PlayerEntity::~PlayerEntity()
{
    
}

void PlayerEntity::Update()
{
    if (!this->attachedToLayer)
        return;
    
    this->extraPositionData->ReassignPositionToEntity();

    if (this->byte69 != 0)
    {
        this->dword70--;

        if (this->dword70 == 0)
        {
            // TODO: call something
        }
    }

    switch (this->byte6A)
    {
        case 0:
            this->extraPositionData->double2 = 0;

            if (this->byte6B)
            {

            }
            else
            {
                this->AssignRenderRectangles(0);
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        default:
            break;
    }

    if (this->dword78 != 0)
        this->dword78--;

    this->AssignRenderRectanglesAdvanced();
    this->byte6B = 0;
    this->word5C = 0;
}

void PlayerEntity::Render()
{
    if ((this->dword78 & 1) == 0)
    {
        AnimatedEntity::Render();
    }
}

void PlayerEntity::SetupRenderingInformation()
{
    AnimatedEntity::SetupRenderingInformation();

    this->byte69 = 0;
    this->dword70 = 0;
    this->byte6B = 0;
    this->unsigned6E = 3;
    this->dword74 = 0;
    this->dword78 = 120;
    this->double80 = 2;
    this->dword90 = 0x1A6; // TODO: Is this correct?
    this->byte6A = 7;
    this->byte6C = 2;

    this->extraPositionData->double1 = 2;
    this->extraPositionData->double2 = 16;

    if (this->dword7C != 0)
    {
        this->extraPositionData->byte38 = -1;
    }
    else
    {
        this->extraPositionData->byte38 = 1;
    }

    this->renderCacheSurface = (this->extraPositionData->byte38 != -1);
    this->extraPositionData->byte39 = -1;

    this->AssignRenderRectangles(3);
}

void PlayerEntity::ReleaseResources()
{
    // TODO: Implement missing stuff
    if (this->byte69)
    {

    }


    AnimatedEntity::ReleaseResources();
}

// ------ Doka_RenderMeta RenderMeta START ------
static const uint16_t Doka_RenderMeta_1_1[] =
{
    180,
    1,
    1,
    1,
    0,
    2,
    2,
    2,
    1,
    1,
    0,
    2,
    4,
    3,
    1,
    1,
    0,
    2,
    2,
    2,
    1,
    1,
    0,
    2,
    114,
    1,
    1,
    1,
    0,
    2,
    2,
    2,
    1,
    1,
    0,
    2,
    4,
    3,
    1,
    1,
    0,
    2,
    2,
    2,
    1,
    1,
    0,
    2,
    6,
    1,
    1,
    1,
    0,
    2,
    2,
    2,
    1,
    1,
    0,
    2,
    4,
    3,
    1,
    1,
    0,
    2,
    2,
    2,
    1,
    1,
    0,
    1,
};

static const uint16_t Doka_RenderMeta_1_2[] =
{
    3,
    30,
    2,
    1,
    0,
    2,
    3,
    31,
    3,
    1,
    0,
    2,
    3,
    32,
    3,
    1,
    0,
    2,
    3,
    33,
    3,
    1,
    0,
    2,
    3,
    34,
    3,
    1,
    0,
    2,
    3,
    35,
    3,
    1,
    0,
    2,
    3,
    36,
    2,
    1,
    0,
    2,
    3,
    37,
    3,
    1,
    0,
    2,
    3,
    38,
    3,
    1,
    0,
    2,
    3,
    39,
    2,
    1,
    0,
    1,
};

static const uint16_t Doka_RenderMeta_1_3[] =
{
    1,
    17,
    1,
    1,
    16,
    2,
    2,
    18,
    1,
    1,
    16,
    2,
    1,
    17,
    1,
    1,
    16,
    0,
    0,
    0,
};

static const uint16_t Doka_RenderMeta_1_4[] =
{
    3,
    21,
    21,
    1,
    16,
    2,
    1,
    22,
    21,
    1,
    16,
    0,
};

static const uint16_t Doka_RenderMeta_1_5[] =
{
    1,
    19,
    1,
    1,
    16,
    0,
    0,
    0,
};

static const uint16_t Doka_RenderMeta_1_6[] =
{
    1,
    17,
    1,
    1,
    0,
    2,
    2,
    18,
    1,
    1,
    0,
    2,
    1,
    17,
    1,
    1,
    0,
    2,
    1,
    1,
    1,
    1,
    0,
    0,
};

static const uint16_t Doka_RenderMeta_1_7[] =
{
    3,
    8,
    1,
    1,
    48,
    2,
    3,
    9,
    1,
    1,
    48,
    2,
    6,
    46,
    46,
    1,
    48,
    2,
    1,
    46,
    46,
    1,
    4144,
    2,
    1,
    47,
    47,
    1,
    48,
    2,
    1,
    48,
    1,
    1,
    48,
    2,
    1,
    49,
    1,
    1,
    48,
    2,
    1,
    48,
    1,
    1,
    48,
    2,
    1,
    47,
    47,
    1,
    48,
    2,
    1,
    46,
    46,
    1,
    48,
    2,
    1,
    47,
    47,
    1,
    48,
    2,
    1,
    48,
    1,
    1,
    48,
    2,
    1,
    49,
    1,
    1,
    48,
    2,
    1,
    48,
    1,
    1,
    48,
    2,
    1,
    47,
    47,
    1,
    48,
    2,
    1,
    46,
    46,
    1,
    48,
    2,
    1,
    47,
    47,
    1,
    48,
    2,
    1,
    48,
    1,
    1,
    48,
    2,
    1,
    49,
    1,
    1,
    48,
    2,
    1,
    48,
    1,
    1,
    48,
    2,
    1,
    47,
    47,
    1,
    48,
    2,
    1,
    46,
    46,
    1,
    48,
    2,
    3,
    10,
    1,
    1,
    0,
    2,
    2,
    9,
    1,
    1,
    0,
    2,
    1,
    1,
    1,
    1,
    0,
    0,
    0,
    0,
};

static const uint16_t Doka_RenderMeta_1_8[] =
{
    3,
    8,
    1,
    1,
    48,
    2,
    2,
    9,
    1,
    1,
    48,
    2,
    5,
    10,
    1,
    1,
    48,
    2,
    2,
    11,
    1,
    1,
    48,
    2,
    1,
    12,
    1,
    1,
    48,
    2,
    1,
    12,
    1,
    1,
    49,
    2,
    2,
    13,
    1,
    1,
    48,
    2,
    2,
    14,
    1,
    1,
    48,
    2,
    5,
    15,
    1,
    1,
    48,
    2,
    3,
    16,
    1,
    1,
    48,
    2,
    3,
    8,
    1,
    1,
    0,
    2,
    1,
    1,
    1,
    1,
    0,
    0,
};

static const uint16_t Doka_RenderMeta_1_9[] =
{
    3,
    40,
    1,
    1,
    48,
    2,
    2,
    41,
    1,
    1,
    48,
    2,
    5,
    42,
    42,
    1,
    48,
    2,
    2,
    23,
    23,
    2,
    48,
    2,
    2,
    24,
    24,
    3,
    48,
    2,
    2,
    43,
    43,
    4,
    48,
    2,
    1,
    28,
    28,
    5,
    49,
    2,
    4,
    29,
    29,
    4,
    48,
    2,
    3,
    45,
    45,
    1,
    0,
    2,
    1,
    1,
    1,
    1,
    0,
    0,
};

static const uint16_t Doka_RenderMeta_1_10[] =
{
    1,
    20,
    1,
    6,
    8240,
    2,
    1,
    20,
    1,
    1,
    48,
    0,
};

static const uint16_t Doka_RenderMeta_1_11[] =
{
    1,
    6,
    1,
    1,
    48,
    2,
    1,
    7,
    1,
    1,
    48,
    1,
};

static const uint16_t Doka_RenderMeta_1_12[] =
{
    2,
    4,
    1,
    0,
    48,
    2,
    2,
    5,
    1,
    0,
    48,
    1,
};

static const uint16_t Doka_RenderMeta_1_13[] =
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

static const uint16_t Doka_RenderMeta_1_14[] =
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

static const uint16_t Doka_RenderMeta_1_15[] =
{
    1,
    50,
    21,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t* Doka_RenderMeta_1[] =
{
    &Doka_RenderMeta_1_1[0],
    &Doka_RenderMeta_1_2[0],
    &Doka_RenderMeta_1_3[0],
    &Doka_RenderMeta_1_4[0],
    &Doka_RenderMeta_1_5[0],
    &Doka_RenderMeta_1_6[0],
    &Doka_RenderMeta_1_7[0],
    &Doka_RenderMeta_1_8[0],
    &Doka_RenderMeta_1_9[0],
    &Doka_RenderMeta_1_10[0],
    &Doka_RenderMeta_1_11[0],
    &Doka_RenderMeta_1_12[0],
    &Doka_RenderMeta_1_13[0],
    &Doka_RenderMeta_1_14[0],
    &Doka_RenderMeta_1_15[0],
    0
};

static const MSRect Doka_RenderMeta_2[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { 0x00, 0x00, 0x30, 0x38 },
    { 0x30, 0x00, 0x60, 0x38 },
    { 0x60, 0x00, 0x90, 0x38 },
    { 0x90, 0x00, 0xc0, 0x38 },
    { 0xc0, 0x00, 0xf0, 0x38 },
    { 0x00, 0x38, 0x30, 0x70 },
    { 0x30, 0x38, 0x60, 0x70 },
    { 0x60, 0x38, 0x90, 0x70 },
    { 0x90, 0x38, 0xc0, 0x70 },
    { 0xc0, 0x38, 0xf0, 0x70 },
    { 0x00, 0x70, 0x30, 0xa8 },
    { 0x30, 0x70, 0x60, 0xa8 },
    { 0x60, 0x70, 0x90, 0xa8 },
    { 0x90, 0x70, 0xc0, 0xa8 },
    { 0xc0, 0x70, 0xf0, 0xa8 },
    { 0x00, 0xa8, 0x30, 0xe0 },
    { 0x30, 0xa8, 0x60, 0xe0 },
    { 0x60, 0xa8, 0x90, 0xe0 },
    { 0x90, 0xa8, 0xc0, 0xe0 },
    { 0xc0, 0xa8, 0xf0, 0xe0 },
    { 0xf0, 0x00, 0x120, 0x40 },
    { 0x120, 0x00, 0x150, 0x40 },
    { 0x150, 0x00, 0x188, 0x40 },
    { 0x188, 0x00, 0x1c0, 0x40 },
    { 0x1c0, 0x00, 0x1f0, 0x40 },
    { 0xf0, 0x40, 0x130, 0x70 },
    { 0x130, 0x40, 0x170, 0x70 },
    { 0x170, 0x40, 0x1a8, 0x70 },
    { 0x1a8, 0x40, 0x1e0, 0x70 },
    { 0xf0, 0x70, 0x120, 0xa8 },
    { 0x120, 0x70, 0x150, 0xa8 },
    { 0x150, 0x70, 0x180, 0xa8 },
    { 0x180, 0x70, 0x1b0, 0xa8 },
    { 0x1b0, 0x70, 0x1e0, 0xa8 },
    { 0xf0, 0xa8, 0x120, 0xe0 },
    { 0x120, 0xa8, 0x150, 0xe0 },
    { 0x150, 0xa8, 0x180, 0xe0 },
    { 0x180, 0xa8, 0x1b0, 0xe0 },
    { 0x1b0, 0xa8, 0x1e0, 0xe0 },
    { 0x00, 0xe0, 0x30, 0x118 },
    { 0x30, 0xe0, 0x60, 0x118 },
    { 0x60, 0xe0, 0x90, 0x118 },
    { 0x90, 0xe0, 0xd0, 0x118 },
    { 0xd0, 0xe0, 0x108, 0x118 },
    { 0x108, 0xe0, 0x140, 0x118 },
    { 0x00, 0x118, 0x40, 0x150 },
    { 0x40, 0x118, 0x80, 0x150 },
    { 0x80, 0x118, 0xb0, 0x150 },
    { 0xb0, 0x118, 0xe0, 0x150 },
    { 0x140, 0xe0, 0x170, 0x120 },
};

static const MSRect Doka_RenderMeta_3[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -32, 0x18, 0x20 },
    { -24, -32, 0x18, 0x20 },
    { -40, -36, 0x10, 0x1c },
    { -40, -36, 0x10, 0x1c },
    { -24, -36, 0x20, 0x1c },
    { -48, -20, 0x10, 0x1c },
    { -48, -20, 0x10, 0x1c },
    { -40, -20, 0x10, 0x1c },
    { -40, -20, 0x10, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -32, -28, 0x10, 0x1c },
    { -48, -28, 0x10, 0x1c },
    { -40, -28, 0x10, 0x1c },
    { -40, -28, 0x10, 0x1c },
    { -32, -28, 0x20, 0x1c },
    { -32, -28, 0x20, 0x1c },
    { -24, -28, 0x18, 0x1c },
    { -24, -28, 0x18, 0x1c },
};

const RenderMeta PlayerEntity_Meta::Doka_RenderMeta =
{
    &Doka_RenderMeta_1[0],
    &Doka_RenderMeta_2[0],
    &Doka_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ Doka_RenderMeta RenderMeta END ------

