#include "BitmapResourceManager.hpp"
#include <string.h>
#include <string>
#include <iostream>

BitmapResourceManager::BitmapResourceManager(uint16_t setID, void* ddPalette, uint16_t secondSetID)
{
    this->ddPalette = ddPalette;
    memset(this->bitmapPtrs, 0, sizeof(this->bitmapPtrs));
    memset(this->bitmapPairObjectPtrs, 0, sizeof(this->bitmapPairObjectPtrs));

    this->LoadBySetID(setID);

    if (secondSetID != 0)
    {
        this->LoadBySetID(secondSetID);
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

    if (cSlot)
    {
        delete cSlot;
        this->bitmapPtrs[aID] = nullptr;
    }

    this->bitmapPtrs[aID] = new Bitmap(aName, nullptr, aID, false);

    if (aID >= 0x11)
    {
        // TODO: Implement pair setup
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

const int16_t* BitmapInformation::LogoScene_ResourceLinkerPtr = LogoScene_ResourceLinker;
const int16_t* BitmapInformation::MenuScene_ResourceLinkerPtr = MenuScene_ResourceLinker;

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

