#pragma once

#include <climits>
#include <string>

class SoundResourceManager
{
    public:
        SoundResourceManager(uint16_t aSetIndex);
        // TODO: Imlement dtor

        void LoadByID(int16_t aID, std::string& aName);
};