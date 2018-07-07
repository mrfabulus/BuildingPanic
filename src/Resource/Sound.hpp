#pragma once

#include <string>
#include <Globals.hpp>

class Sound
{
    private:
        std::string soundName;

    public:
        Sound(std::string& aSoundName);
        ~Sound();
};