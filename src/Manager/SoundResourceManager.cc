#include "Manager/SoundResourceManager.hpp"
#include <iostream>
#include "Resource/Sound.hpp"

SoundResourceManager::SoundResourceManager(uint16_t aSetIndex)
{
    this->music = nullptr;

    memset(&this->soundSlots, 0, sizeof(this->soundSlots));
    this->LoadBySetID(aSetIndex);
}

SoundResourceManager::~SoundResourceManager()
{
    if (this->music != nullptr)
    {
        Mix_FreeMusic(this->music);
        this->music = nullptr;
    }
}

void SoundResourceManager::LoadBySetID(uint16_t aSetID)
{
    int16_t* ptr = nullptr;

    switch(aSetID)
    {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
            ptr = (int16_t*) SoundInformation::Sound_Select_Ok_ResourceLinkerPtr;
            break;
        case 7:
            ptr = (int16_t*) SoundInformation::Sound_1_ResourceLinkerPtr;
            break;
        case 8:
            ptr = (int16_t*) SoundInformation::Sound_2_ResourceLinkerPtr;
            break;
        case 9:
            ptr = (int16_t*) SoundInformation::Sound_3_ResourceLinkerPtr;
            break;
        case 10:
            ptr = (int16_t*) SoundInformation::Sound_4_ResourceLinkerPtr;
            break;
        case 11:
            ptr = (int16_t*) SoundInformation::Sound_5_ResourceLinkerPtr;
            break;
        default:
            break;
    }

    if (ptr != nullptr)
    {
        while(*ptr != -1)
        {
            int16_t sID = *ptr;
            std::string soundName = SoundInformation::WavNames[sID];

            std::cout << "Loading sound " << soundName << " with ID " << sID << std::endl;
            this->LoadByID(sID, soundName);

            ptr++;
        }
    }
}

void SoundResourceManager::LoadByID(int16_t aID, std::string& aName)
{
    if (aID >= 0x40)
        return;

    this->soundSlots[aID] = new Sound(aName);
}

void SoundResourceManager::PlayMidi(std::string midiName)
{
    if (this->music != nullptr)
    {
        Mix_FreeMusic(this->music);
        this->music = nullptr;
    }

    this->music = Mix_LoadMUS(("../assets/midi/" + midiName).c_str());

    if(Mix_PlayMusic(this->music, 1) == -1)
    {
        printf("Couldn't play midi\n");
        return;
    }
}

void SoundResourceManager::PlaySoundSlot(uint16_t aSlotID, uint32_t aDuration)
{
    // TODO: Duration ?
    if (this->soundSlots[aSlotID] != nullptr)
    {
        this->soundSlots[aSlotID]->Play();
    }
}

static const int16_t Sound_Select_Ok_ResourceLinker[] = 
{
    0,
    1,
    -1
};

static const int16_t Sound_1_ResourceLinker[] = 
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xA,
    0xB,
    0xC,
    0xD,
    0xE,
    0xF,
    0x20,
    -1
};

static const int16_t Sound_2_ResourceLinker[] = 
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xA,
    0xB,
    0xC,
    0xD,
    0x10,
    0x11,
    0x20,
    -1
};

static const int16_t Sound_3_ResourceLinker[] = 
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xA,
    0xB,
    0xC,
    0xD,
    0x12,
    0x13,
    0x14,
    0x15,
    0x16,
    0xF,
    0x20,
    -1
};

static const int16_t Sound_4_ResourceLinker[] = 
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    0x17,
    9,
    0xA,
    0xB,
    0xC,
    0xD,
    0x18,
    0x19,
    0x1A,
    0x1B,
    0xF,
    0x20,
    -1
};

static const int16_t Sound_5_ResourceLinker[] = 
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xA,
    0xB,
    0xC,
    0xD,
    0x1C,
    0x1D,
    0x1E,
    0x1F,
    0x20,
    -1
};

std::string const SoundInformation::WavNames[] =
{
    "SE_OK",
    "SE_SELECT",
    "SE_JUMP",
    "SE_LAND",
    "SE_HIT",
    "SE_HIT2",
    "SE_FALL",
    "SE_FALL2",
    "SE_PIYO",
    "SE_THROW",
    "SE_WALL_CRUSH",
    "SE_GET_ITEM",
    "SE_GET_SCORE",
    "SE_ENEMY_JUMP",
    "SE_BIKE_SLIP",
    "SE_BIKE_FUKASHI",
    "SE_HIT_FALL",
    "SE_BOSS2_HOT",
    "SE_HIT_OIL",
    "SE_HIT_DRUM",
    "SE_HIT_FIRE",
    "SE_BOSS3_BOUND",
    "SE_BOSS3_FIRE",
    "SE_PIYO2",
    "SE_HIT_ELEC",
    "SE_BOSS4_BEAM",
    "SE_BOSS4_ELBALL",
    "SE_BOSS4_JET",
    "SE_HIT_IBALL",
    "SE_BOSS5_GACHA",
    "SE_BOSS5_MOVE",
    "SE_BOSS5_STOP",
    "SE_DORON_RUN"
};

const int16_t* SoundInformation::Sound_Select_Ok_ResourceLinkerPtr = Sound_Select_Ok_ResourceLinker;
const int16_t* SoundInformation::Sound_1_ResourceLinkerPtr = Sound_1_ResourceLinker;
const int16_t* SoundInformation::Sound_2_ResourceLinkerPtr = Sound_2_ResourceLinker;
const int16_t* SoundInformation::Sound_3_ResourceLinkerPtr = Sound_3_ResourceLinker;
const int16_t* SoundInformation::Sound_4_ResourceLinkerPtr = Sound_4_ResourceLinker;
const int16_t* SoundInformation::Sound_5_ResourceLinkerPtr = Sound_5_ResourceLinker;
