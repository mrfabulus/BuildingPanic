#include <string.h>
#include "Manager/Level/LevelManager_Normal.hpp"
#include "Manager/SaveManager.hpp"
#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"
#include "Entity/Stage/PlayerEntity.hpp"
#include "Entity/Generic/StaticPictureEntity.hpp"
#include "Entity/HUD/HudHeartEntity.hpp"
#include "Manager/BitmapResourceManager.hpp"
#include "Entity/UI/FontTileSetEntity.hpp"
#include "Entity/UI/ScoreTileSetEntity2.hpp"
#include "Scene/MenuScene.hpp"
#include "Entity/Stage/WallEntity.hpp"

LevelManager_Normal::LevelManager_Normal(Ingame_BasicStage_Scene* aScene)
    : LevelManager_base(aScene)
{
    printf("LevelManager_Normal::ctor\n");
    this->levelPhase = 0;
    this->dwordE4 = 0;
    this->dwordE8 = 0;
    this->dwordC4[0] = nullptr;
    this->dwordC4[1] = nullptr;
    this->dwordCC[0] = nullptr;
    this->dwordCC[1] = nullptr;
    this->dwordCC[2] = nullptr;
    this->dwordCC[3] = nullptr;
    this->dwordDC = 0;
    this->wordE0 = 0;
    this->dword88 = nullptr;
    memset(this->buffer8C, 0, sizeof(this->buffer8C));

    if (this->CreateEntities())
    {
        this->scene->player1Entity->dword9C = this->scene->hudHeartP1;
        uint16_t heartsLeft = this->scene->saveManager->playerObject1.heartsLeft;
        this->scene->hudHeartP1->heartsLeft = heartsLeft;
        this->scene->hudHeartP1->AssignRenderRectangles(heartsLeft);
        this->scene->hudScoreP1->dword4C = this->scene->saveManager->playerObject1.score;

        if (this->scene->saveManager->Is2PMode())
        {
            this->scene->player2Entity->dword9C = this->scene->hudHeartP2;
            heartsLeft = this->scene->saveManager->playerObject2.heartsLeft;
            this->scene->hudHeartP2->heartsLeft = heartsLeft;
            this->scene->hudHeartP2->AssignRenderRectangles(heartsLeft);
            this->scene->hudScoreP2->dword4C = this->scene->saveManager->playerObject2.score;
        }

        this->PrepareLevel();
        this->PrepareWalls();
    }
}

LevelManager_Normal::~LevelManager_Normal()
{
}

bool LevelManager_Normal::CreateEntities()
{
    // TODO: Create enemy factories

    for (uint32_t i = 0; i < 2; i++)
    {
         // BMP_SCORE - Score number font
        this->dwordC4[i] = new FontTileSetEntity(this->scene, this->scene->sceneBitmapMgr->bitmapPtrs[21], 0);
    }

    for (uint32_t i = 0; i < 4; i++)
    {
        // Create score tiles
        this->dwordCC[i] = new ScoreTileSetEntity2(this->scene, this->scene->sceneBitmapMgr->bitmapPtrs[21], 1);
    }

    // CURSOR
    this->dword88 = new StaticPictureEntity(this->scene, this->scene->sceneBitmapMgr->bitmapPtrs[37], &MenuScene_Meta::SelectCursorEntity_RenderMeta, 0);
    this->dword88->SetLayerIndex(4);
    this->dword88->dword10 = 0;

    for (uint32_t i = 0; i < 14; i++)
    {
        // WNDMSG
        this->buffer8C[i] = new StaticPictureEntity(this->scene, this->scene->sceneBitmapMgr->bitmapPtrs[36], &LevelManager_Normal_Meta::WindowMsg_RenderMeta, 0);
        this->buffer8C[i]->SetLayerIndex(4);
        this->buffer8C[i]->dword10 = 0;
    }

    return true;
}

void LevelManager_Normal::PrepareLevel()
{
    printf("LevelManager_Normal::PrepareLevel()\n");
    this->scene->AttachLamps();

    uint16_t nextLvl = this->scene->saveManager->GetNextLevel();
    uint32_t playerCount = this->scene->saveManager->GetPlayerCount();
    uint32_t stageRelated = this->scene->saveManager->nextStage - 5;
    uint32_t index = (((playerCount + stageRelated) * 5) * 6) + nextLvl;
    
    // TODO: Dump struct
    LevelInfoEntry* infoRef[] = { 0 };

    /*
    if (infoRef != nullptr)
    {
        for (uint32_t i = 0; i < 8; i++)
        {
            LevelInfoType type = infoRef[i]->infoType;

            if (type == LevelInfoType_Terminator)
                break;

            // TODO: Implement
            switch (type)
            {
                case LevelInfoType_ItemInfo:
                    break;
                case LevelInfoType_EnemyInfo:
                    break;
            }
        }
    }
    */
}

void LevelManager_Normal::PrepareWalls()
{
    uint16_t nextLvl = this->scene->saveManager->GetNextLevel();
    uint16_t levelIndex = (this->scene->saveManager->nextStage * 6) + nextLvl;

    // TODO: Struct
    uint8_t levelExample[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    for (uint32_t i = 0; i < 32; i++)
    {
        if (levelExample[i] != 0)
            this->scene->wallEntities[i]->PreSet(WallOwner_Garcia);
    }
}

void LevelManager_Normal::F2()
{
}

void LevelManager_Normal::Init()
{
    if (this->scene->ticksLeftUntilReEval <= 0)
    {
        uint32_t nextLvl = this->scene->saveManager->GetNextLevel();
        uint32_t playerCount = this->scene->saveManager->GetPlayerCount();
        uint32_t index = nextLvl + 6 * playerCount;
        // TODO: Dump struct \/
        this->dwordE8 = 0;
        this->scene->scenePhaseIndex = 1;
    }

    this->scene->RefreshHighScore();
}

void LevelManager_Normal::Update()
{
    if (this->F7())
    {
        this->scene->gridImageEntity->AttachWithPosition(320, 240, 0);
        this->scene->scenePhaseIndex = 16;
        this->levelPhase = 0;
    }
    else if (this->IsLevelOver())
    {
        this->scene->scenePhaseIndex = 17;

        if (this->scene->saveManager->saveState.unk2 != 0)
        {
            this->scene->gridImageEntity->AttachWithPosition(320, 240, 0);
            this->levelPhase = 0;
        }
        else
        {
            this->scene->saveManager->lastStageStatus = 2;
            this->scene->ticksLeftUntilReEval = 180;
            this->levelPhase = 2;
        }
    }

    if (this->scene->saveManager->IsFlagMaskEnabledAny(0x1000))
    {
        if (this->scene->saveManager->IsFlagMaskEnabledAny(2))
        {
            // this->scene->Offset 30 in VTable();
        }
        else
        {
            // this->scene->Offset 2C in VTable();
        }
    }

    if (this->scene->player1Entity->attachedToLayer)
    {
        // ->??()
    }
    
    // ???

    this->scene->RefreshHighScore();

}

void LevelManager_Normal::F5()
{
}

void LevelManager_Normal::F6()
{
}

bool LevelManager_Normal::IsLevelOver()
{
    return false;
}

void LevelManager_Normal::F9()
{
}

// ------ WindowMsg RenderMeta START ------
static const uint16_t WindowMsg_RenderMeta_1_1[] =
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

static const uint16_t WindowMsg_RenderMeta_1_2[] =
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

static const uint16_t WindowMsg_RenderMeta_1_3[] =
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

static const uint16_t WindowMsg_RenderMeta_1_4[] =
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

static const uint16_t WindowMsg_RenderMeta_1_5[] =
{
    16,
    0,
    0,
    0,
    0,
    2,
    16,
    5,
    5,
    0,
    0,
    1,
};

static const uint16_t WindowMsg_RenderMeta_1_6[] =
{
    16,
    0,
    0,
    0,
    0,
    2,
    16,
    6,
    6,
    0,
    0,
    1,
};

static const uint16_t WindowMsg_RenderMeta_1_7[] =
{
    1,
    19,
    19,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_8[] =
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

static const uint16_t WindowMsg_RenderMeta_1_9[] =
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

static const uint16_t WindowMsg_RenderMeta_1_10[] =
{
    1,
    9,
    9,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_11[] =
{
    1,
    10,
    10,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_12[] =
{
    1,
    11,
    11,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_13[] =
{
    1,
    12,
    12,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_14[] =
{
    1,
    13,
    13,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_15[] =
{
    1,
    14,
    14,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_16[] =
{
    1,
    15,
    15,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_17[] =
{
    1,
    16,
    16,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_18[] =
{
    1,
    17,
    17,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_19[] =
{
    16,
    25,
    23,
    0,
    0,
    2,
    16,
    15,
    15,
    0,
    0,
    1,
};

static const uint16_t WindowMsg_RenderMeta_1_20[] =
{
    16,
    26,
    15,
    0,
    0,
    2,
    16,
    16,
    16,
    0,
    0,
    1,
};

static const uint16_t WindowMsg_RenderMeta_1_21[] =
{
    16,
    0,
    0,
    0,
    0,
    2,
    16,
    17,
    17,
    0,
    0,
    1,
};

static const uint16_t WindowMsg_RenderMeta_1_22[] =
{
    1,
    18,
    18,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_23[] =
{
    1,
    20,
    20,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_24[] =
{
    1,
    27,
    2,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_25[] =
{
    1,
    21,
    21,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_26[] =
{
    1,
    22,
    21,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_27[] =
{
    1,
    23,
    22,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_28[] =
{
    1,
    24,
    22,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_29[] =
{
    1,
    28,
    24,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_30[] =
{
    1,
    29,
    25,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_31[] =
{
    1,
    30,
    24,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_32[] =
{
    1,
    31,
    26,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t WindowMsg_RenderMeta_1_33[] =
{
    1,
    32,
    26,
    0,
    0,
    0,
    0,
    0,
};

static const uint16_t* WindowMsg_RenderMeta_1[] =
{
    &WindowMsg_RenderMeta_1_1[0],
    &WindowMsg_RenderMeta_1_2[0],
    &WindowMsg_RenderMeta_1_3[0],
    &WindowMsg_RenderMeta_1_4[0],
    &WindowMsg_RenderMeta_1_5[0],
    &WindowMsg_RenderMeta_1_6[0],
    &WindowMsg_RenderMeta_1_7[0],
    &WindowMsg_RenderMeta_1_8[0],
    &WindowMsg_RenderMeta_1_9[0],
    &WindowMsg_RenderMeta_1_10[0],
    &WindowMsg_RenderMeta_1_11[0],
    &WindowMsg_RenderMeta_1_12[0],
    &WindowMsg_RenderMeta_1_13[0],
    &WindowMsg_RenderMeta_1_14[0],
    &WindowMsg_RenderMeta_1_15[0],
    &WindowMsg_RenderMeta_1_16[0],
    &WindowMsg_RenderMeta_1_17[0],
    &WindowMsg_RenderMeta_1_18[0],
    &WindowMsg_RenderMeta_1_19[0],
    &WindowMsg_RenderMeta_1_20[0],
    &WindowMsg_RenderMeta_1_21[0],
    &WindowMsg_RenderMeta_1_22[0],
    &WindowMsg_RenderMeta_1_23[0],
    &WindowMsg_RenderMeta_1_24[0],
    &WindowMsg_RenderMeta_1_25[0],
    &WindowMsg_RenderMeta_1_26[0],
    &WindowMsg_RenderMeta_1_27[0],
    &WindowMsg_RenderMeta_1_28[0],
    &WindowMsg_RenderMeta_1_29[0],
    &WindowMsg_RenderMeta_1_30[0],
    &WindowMsg_RenderMeta_1_31[0],
    &WindowMsg_RenderMeta_1_32[0],
    &WindowMsg_RenderMeta_1_33[0],
    0
};

static const MSRect WindowMsg_RenderMeta_2[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { 0x10, 0x00, 0x70, 0x10 },
    { 0x80, 0x10, 0xd0, 0x20 },
    { 0x00, 0x00, 0x70, 0x10 },
    { 0x70, 0x00, 0xe0, 0x10 },
    { 0x00, 0x30, 0x70, 0x40 },
    { 0x70, 0x30, 0xd0, 0x40 },
    { 0x00, 0x20, 0x50, 0x30 },
    { 0x50, 0x20, 0xa0, 0x30 },
    { 0x00, 0x40, 0xd0, 0x50 },
    { 0x00, 0x50, 0xc0, 0x60 },
    { 0x00, 0x50, 0xd0, 0x60 },
    { 0x00, 0x60, 0xa0, 0x70 },
    { 0x00, 0x70, 0xd0, 0x90 },
    { 0x00, 0x90, 0xd0, 0xa0 },
    { 0xa0, 0x20, 0xd0, 0x30 },
    { 0x00, 0x10, 0x40, 0x20 },
    { 0x40, 0x10, 0x80, 0x20 },
    { 0xd0, 0x10, 0xe0, 0x90 },
    { 0x00, 0xb0, 0x60, 0xc0 },
    { 0x50, 0xb0, 0x90, 0xc0 },
    { 0x00, 0xa0, 0x18, 0xb0 },
    { 0x18, 0xa0, 0x30, 0xb0 },
    { 0x30, 0xa0, 0x40, 0xb0 },
    { 0x40, 0xa0, 0x50, 0xb0 },
    { 0x58, 0xc0, 0x98, 0xd8 },
    { 0x50, 0xa0, 0x80, 0xb0 },
    { 0x80, 0xa0, 0xd0, 0xb0 },
    { 0x00, 0xc0, 0x20, 0xd8 },
    { 0x20, 0xc0, 0x38, 0xd8 },
    { 0x38, 0xc0, 0x58, 0xd8 },
    { 0x90, 0xb0, 0xb0, 0xb8 },
    { 0x90, 0xb8, 0xb0, 0xc0 },
};

static const MSRect WindowMsg_RenderMeta_3[] =
{
    { 0x00, 0x00, 0x01, 0x01 },
    { -48, -8, 0x30, 0x08 },
    { -40, -8, 0x28, 0x08 },
    { -56, -8, 0x38, 0x08 },
    { -56, -8, 0x38, 0x08 },
    { -56, -8, 0x38, 0x08 },
    { -48, -8, 0x30, 0x08 },
    { -40, -8, 0x28, 0x08 },
    { -40, -8, 0x28, 0x08 },
    { -104, -8, 0x68, 0x08 },
    { -96, -8, 0x60, 0x08 },
    { -104, -8, 0x68, 0x08 },
    { -80, -8, 0x50, 0x08 },
    { -104, -16, 0x68, 0x10 },
    { -104, -8, 0x68, 0x08 },
    { -24, -8, 0x18, 0x08 },
    { -32, -8, 0x20, 0x08 },
    { -32, -8, 0x20, 0x08 },
    { -8, -64, 0x08, 0x40 },
    { -48, -8, 0x30, 0x08 },
    { -32, -8, 0x20, 0x08 },
    { -12, -8, 0x0c, 0x08 },
    { -8, -8, 0x08, 0x08 },
    { -32, -12, 0x20, 0x0c },
    { -16, -12, 0x10, 0x0c },
    { -12, -12, 0x0c, 0x0c },
    { -16, 0x00, 0x10, 0x08 },
};

const RenderMeta LevelManager_Normal_Meta::WindowMsg_RenderMeta =
{
    &WindowMsg_RenderMeta_1[0],
    &WindowMsg_RenderMeta_2[0],
    &WindowMsg_RenderMeta_3[0],
    gConsts::RenderMetaTerminatorPtr
};
// ------ WindowMsg RenderMeta END ------
