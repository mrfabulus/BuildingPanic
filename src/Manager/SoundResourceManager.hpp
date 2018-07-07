#pragma once

#include <cstdint>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <Resource/Sound.hpp>

struct SoundInformation
{
    static const std::string WavNames[];
    static const std::string MidiNames[];

    static const int16_t* Sound_Select_Ok_ResourceLinkerPtr;
    static const int16_t* Sound_1_ResourceLinkerPtr;
    static const int16_t* Sound_2_ResourceLinkerPtr;
    static const int16_t* Sound_3_ResourceLinkerPtr;
    static const int16_t* Sound_4_ResourceLinkerPtr;
    static const int16_t* Sound_5_ResourceLinkerPtr;
};

class SoundResourceManager
{
    private:
        Mix_Chunk* wav;
        Mix_Music* music;
    public:
        SoundResourceManager(uint16_t aSetIndex);
        ~SoundResourceManager();

        void LoadBySetID(uint16_t aSetID);
        void LoadByID(int16_t aID, std::string& aName);
};