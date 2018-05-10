#include <string.h>
#include <string>
#include <iostream>

#include "Manager/BitmapResourceManager.hpp"
#include "Resource/Bitmap.hpp"
#include "Resource/BitmapCacheSurface.hpp"

BitmapResourceManager::BitmapResourceManager(uint16_t setID, void* ddPalette, uint16_t secondSetID)
{
    this->ddPalette = ddPalette;
    memset(this->bitmapPtrs, 0, sizeof(this->bitmapPtrs));
    memset(this->bitmapCachePtrs, 0, sizeof(this->bitmapCachePtrs));

    this->LoadBySetID(setID);

    if (secondSetID != 0)
    {
        this->LoadBySetID(secondSetID);
    }
}

BitmapResourceManager::~BitmapResourceManager()
{
    for (int i = 0; i < 128; i++)
    {
        if (this->bitmapPtrs[i] != nullptr)
        {
            delete this->bitmapPtrs[i];
            this->bitmapPtrs[i] = nullptr;
        }

        if (this->bitmapCachePtrs[i] != nullptr)
        {
            delete this->bitmapCachePtrs[i];
            this->bitmapCachePtrs[i] = nullptr;
        }
    }
}

void BitmapResourceManager::LoadBySetID(uint16_t setID)
{
    int16_t* setPtr = nullptr;

    switch (setID)
    {
        case 0:
            setPtr = (int16_t*) BitmapInformation::LogoScene_ResourceLinkerPtr;
            break;
        case 1:
            setPtr = (int16_t*) BitmapInformation::MenuScene_ResourceLinkerPtr;
            break;
        case 2:
            // Intentionally left as zero to preserve original behavior of the binary
            break;
        case 3:
            setPtr = (int16_t*) BitmapInformation::CharacterChoice_ResourceLinkerPtr;
            break;
        case 4:
            setPtr = (int16_t*) BitmapInformation::ScoreboardScene_ResourceLinkerPtr;
            break;
        case 5:
            setPtr = (int16_t*) BitmapInformation::StageStatusScene_ResourceLinkerPtr;
            break;
        case 6:
            setPtr = (int16_t*) BitmapInformation::AfterGameCreditsScene_ResourceLinkerPtr;
            break;
        case 7:
            setPtr = (int16_t*) BitmapInformation::IngameStage1_ResourceLinkerPtr;
            break;
        case 8:
            setPtr = (int16_t*) BitmapInformation::IngameStage2_ResourceLinkerPtr;
            break;
        case 9:
            setPtr = (int16_t*) BitmapInformation::IngameStage3_ResourceLinkerPtr;
            break;
        case 10:
            setPtr = (int16_t*) BitmapInformation::IngameStage4_ResourceLinkerPtr;
            break;
        case 11:
            setPtr = (int16_t*) BitmapInformation::IngameStage5_ResourceLinkerPtr;
            break;
        default:
            break;
    }

    while (*setPtr != -1)
    {
        int16_t cID = *setPtr;
        std::string resourceName = BitmapInformation::Names[cID];

        std::cout << "Loading resource " << resourceName << " with ID " << cID << std::endl;
        this->LoadByID(resourceName, cID);

        setPtr++;
    }
}

void BitmapResourceManager::LoadByID(std::string& aName, int16_t aID)
{
    if (aID >= 0x80)
        return;

    Bitmap* cSlot = this->bitmapPtrs[aID];

    // Check if bitmap is loaded at same slot
    if (cSlot)
    {
        delete cSlot;
        this->bitmapPtrs[aID] = nullptr;
    }

    this->bitmapPtrs[aID] = new Bitmap(aName, nullptr, aID, false);

    if (aID >= 0x11)
    {
        BitmapCacheSurface* cSlot2 = this->bitmapCachePtrs[aID];

        // Check if bitmap pair is loaded at same slot
        if (cSlot2)
        {
            delete cSlot2;
            this->bitmapCachePtrs[aID] = nullptr;
        }

        this->bitmapCachePtrs[aID] = new BitmapCacheSurface(this->bitmapPtrs[aID]);
    }
}

static const int16_t LogoScene_ResourceLinker[] =
{
    0x11, // BMP_LOGO
    -1
};

static const int16_t MenuScene_ResourceLinker[] =
{
    0x21, // BMP_PMARK
    0x2C, // BMP_TITLE
    0x47, // BMP_PANEL
    0x36, // BMP_CRIGHT
    0x35, // BMP_MODESEL
    0x25, // BMP_CURSOR
    0x16, // BMP_MOJI
    0x50, // BMP_OPTION
    -1
};

static const int16_t CharacterChoice_ResourceLinker[] =
{
    0x2E,
    0x31,
    0x3A,
    0x43,
    0x44,
    0x48,
    -1
};

static const int16_t ScoreboardScene_ResourceLinker[] =
{
    0x2B,
    0x2F,
    0x33,
    0x34,
    0x32,
    0x22,
    0x25,
    0x16,
    0x21,
    0x2D,
    -1
};

static const int16_t StageStatusScene_ResourceLinker[] =
{
    0x26,
    0x27,
    0x28,
    0x29,
    0x2A,
    0x30,
    0x24,
    0x45,
    0x0F,
    0x12,
    -1
};

static const int16_t AfterGameCreditsScene_ResourceLinker[] =
{
    0x0,
    0x1,
    0x0E,
    0x12,
    0x14,
    0x4A,
    0x4B,
    0x4C,
    0x4D,
    0x4E,
    -1
};

static const int16_t IngameStage1_ResourceLinker[] =
{
    0x0,
    0x1,
    0x0E,
    0x12,
    0x14,
    0x15,
    0x17,
    0x18,
    0x19,
    0x1A,
    0x1E,
    0x8,
    0x9,
    0x0A,
    0x0B,
    0x2,
    0x3,
    0x49,
    0x1D,
    0x3C,
    0x20,
    0x21,
    0x23,
    0x24,
    0x25,
    0x26,
    0x3B,
    0x1B,
    0x38,
    0x1C,
    0x42,
    0x37,
    -1
};

static const int16_t IngameStage2_ResourceLinker[] =
{
    0x0,
    0x1,
    0x0E,
    0x12,
    0x14,
    0x15,
    0x17,
    0x18,
    0x19,
    0x1A,
    0x1E,
    0x8,
    0x9,
    0x0A,
    0x0B,
    0x4,
    0x1D,
    0x3C,
    0x1F,
    0x20,
    0x21,
    0x23,
    0x24,
    0x25,
    0x27,
    0x3B,
    0x1B,
    0x38,
    0x1C,
    0x42,
    0x37,
    -1
};

static const int16_t IngameStage3_ResourceLinker[] =
{
    0x0,
    0x1,
    0x0E,
    0x12,
    0x14,
    0x15,
    0x17,
    0x18,
    0x19,
    0x1A,
    0x1E,
    0x8,
    0x9,
    0x0A,
    0x0B,
    0x0C,
    0x5,
    0x1D,
    0x3C,
    0x20,
    0x21,
    0x23,
    0x24,
    0x25,
    0x28,
    0x3B,
    0x1B,
    0x39,
    0x10,
    0x40,
    0x38,
    0x1C,
    0x42,
    -1
};

static const int16_t IngameStage4_ResourceLinker[] =
{
    0x0,
    0x1,
    0x0E,
    0x12,
    0x13,
    0x14,
    0x15,
    0x17,
    0x18,
    0x19,
    0x1A,
    0x1E,
    0x8,
    0x9,
    0x0A,
    0x0B,
    0x0C,
    0x3C,
    0x6,
    0x7,
    0x3E,
    0x3F,
    0x41,
    0x1D,
    0x20,
    0x21,
    0x23,
    0x24,
    0x25,
    0x29,
    0x3B,
    0x1B,
    0x3D,
    0x38,
    0x1C,
    0x42,
    -1
};

static const int16_t IngameStage5_ResourceLinker[] =
{
    0x0,
    0x1,
    0x0E,
    0x12,
    0x14,
    0x15,
    0x17,
    0x18,
    0x19,
    0x1A,
    0x1E,
    0x8,
    0x9,
    0x0A,
    0x0B,
    0x46,
    0x1D,
    0x3C,
    0x20,
    0x21,
    0x23,
    0x24,
    0x25,
    0x2A,
    0x3B,
    0x1B,
    0x1C,
    0x42,
    -1
};

const int16_t* BitmapInformation::LogoScene_ResourceLinkerPtr = LogoScene_ResourceLinker;
const int16_t* BitmapInformation::MenuScene_ResourceLinkerPtr = MenuScene_ResourceLinker;
const int16_t* BitmapInformation::CharacterChoice_ResourceLinkerPtr = CharacterChoice_ResourceLinker;
const int16_t* BitmapInformation::ScoreboardScene_ResourceLinkerPtr = ScoreboardScene_ResourceLinker;
const int16_t* BitmapInformation::StageStatusScene_ResourceLinkerPtr = StageStatusScene_ResourceLinker;
const int16_t* BitmapInformation::AfterGameCreditsScene_ResourceLinkerPtr = AfterGameCreditsScene_ResourceLinker;
const int16_t* BitmapInformation::IngameStage1_ResourceLinkerPtr = IngameStage1_ResourceLinker;
const int16_t* BitmapInformation::IngameStage2_ResourceLinkerPtr = IngameStage2_ResourceLinker;
const int16_t* BitmapInformation::IngameStage3_ResourceLinkerPtr = IngameStage3_ResourceLinker;
const int16_t* BitmapInformation::IngameStage4_ResourceLinkerPtr = IngameStage4_ResourceLinker;
const int16_t* BitmapInformation::IngameStage5_ResourceLinkerPtr = IngameStage5_ResourceLinker;

std::string const BitmapInformation::Names[] =
{
    "DOKA",
    "TOBI",
    "BOSS1",
    "BIKE",
    "BOSS2",
    "BOSS3",
    "BOSS4_B",
    "BOSS4_R",
    "ENEMY1",
    "ENEMY2",
    "ENEMY3",
    "ENEMY4",
    "ENEMY5",
    "DORON",
    "WEAPON",
    "CHR_AFTER",
    "DRUM_STG03",
    "LOGO",
    "PIYO",
    "PIYO2",
    "HIT",
    "SCORE",
    "MOJI",
    "ITEM",
    "MINI",
    "WALL",
    "WALL2",
    "PATO",
    "HP",
    "BOSSFACE",
    "MHEART",
    "FALL",
    "COCKPIT",
    "PMARK",
    "ENDMARK",
    "WINDOW",
    "WNDMSG",
    "CURSOR",
    "BG_STG01",
    "BG_STG02",
    "BG_STG03",
    "BG_STG04",
    "BG_STG05",
    "BG_RANKING",
    "TITLE",
    "LOGO_SUB",
    "LOGO_SELECT",
    "LOGO_RANKING",
    "LOGO_AFTER",
    "MESSAGE_SELECT",
    "MESSAGE_RANKING",
    "RANK",
    "RANK_HED",
    "MODESEL",
    "CRIGHT",
    "DEMOPLAY",
    "SMOKE",
    "FIRE",
    "BG_SELECT",
    "BGBAR_STG01",
    "WEAPON1_ENEMY",
    "ELEC_STG04",
    "BEAM_STG04",
    "E_BALL_STG04",
    "OIL_STG03",
    "EFFECT_BOSS4",
    "PAUSE",
    "CURSOR_SELECT",
    "MAPQ_SELECT",
    "PETAL",
    "BOSS5",
    "PANEL",
    "CHAR_SELECT",
    "SPARK",
    "ENDPIC_1",
    "ENDPIC_2",
    "ENDPIC_3",
    "ENDPIC_4",
    "FILMSIDE",
    "WINCUP",
    "OPTION",
    "DOKA_LOGO"
};

