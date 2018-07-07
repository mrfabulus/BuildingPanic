#pragma once

#include <string>
#include <Globals.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound
{
    private:
        Mix_Chunk* wav;
        std::string soundName;

    public:
        Sound(std::string& aSoundName);
        ~Sound();

        void Play();
};