#pragma once

#include <cstdint>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

struct SoundInformation
{
    static const std::string WavNames[];
    static const std::string MidiNames[];
};

class SoundResourceManager
{
    private:
        Mix_Chunk* wav;
        Mix_Music* music;
    public:
        SoundResourceManager(uint16_t aSetIndex);
        
        ~SoundResourceManager();

        void LoadByID(int16_t aID, std::string& aName);
};