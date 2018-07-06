#pragma once

#include <string>
#include <Globals.hpp>

class Sound
{
    private:
        string soundName;

    public:
        Sound(string& aSoundName);

        ~Sound();
};