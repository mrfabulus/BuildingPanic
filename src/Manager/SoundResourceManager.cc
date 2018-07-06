#include "Manager/SoundResourceManager.hpp"

SoundResourceManager::SoundResourceManager(uint16_t aSetIndex)
{
    printf("SRM ctor: %d\n", aSetIndex);

    this->wav = Mix_LoadWAV("../assets/sounds/SE_SELECT.wav");
    this->music = Mix_LoadMUS("../assets/midi/BPBGM01.MID");

    if(this->wav == NULL)
    {
        printf("Wav NULL\n");
        return;
    }

    if(this->music == NULL)
    {
        printf("Music NULL\n");
        return;
    }
}

SoundResourceManager::~SoundResourceManager()
{
    Mix_FreeChunk(this->wav);
    Mix_FreeMusic(this->music);
}

void SoundResourceManager::LoadByID(int16_t aID, std::string& aName)
{
    if (aID >= 0x40)
        return;
    
    std::string asd = "BPBGM01.MID";
    if(!aName.compare(asd))
    {
        if(Mix_PlayMusic(this->music, 1) == -1)
        {
            printf("Couldn't play midi\n");
            return;
        }
    }
    else
    {
        if( Mix_PlayChannel(-1, this->wav, 0) == -1)
        {
            printf("Couldn'T play wav\n");
            return;
        }
    }

    //Mix_Playing(channel);

    //Mix_FreeChunk(wav);

    // TODO: Load Sound
}

std::string const SoundInformation::WavNames[] =
{
    "SE_BIKE_FUKASHI",
    "SE_BIKE_SLIP",
    "SE_BOSS2_HOT",
    "SE_BOSS3_BOUND",
    "SE_BOSS3_FIRE",
    "SE_BOSS4_BEAM",
    "SE_BOSS4_ELBALL",
    "SE_BOSS4_JET",
    "SE_BOSS5_GACHA",
    "SE_BOSS5_MOVE",
    "SE_BOSS5_STOP",
    "SE_DORON_RUN",
    "SE_ENEMY_JUMP",
    "SE_FALL",
    "SE_FALL2",
    "SE_GET_ITEM",
    "SE_GET_SCORE",
    "SE_HIT_DRUM",
    "SE_HIT_ELEC",
    "SE_HIT_FALL",
    "SE_HIT_FIRE",
    "SE_HIT_IBALL",
    "SE_HIT_OIL",
    "SE_HIT",
    "SE_HIT2",
    "SE_JUMP",
    "SE_LAND",
    "SE_OK",
    "SE_PIYO",
    "SE_PIYO2",
    "SE_SELECT",
    "SE_THROW",
    "SE_WALL_CRUSH"
};