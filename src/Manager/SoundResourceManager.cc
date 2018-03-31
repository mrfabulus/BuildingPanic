#include "SoundResourceManager.hpp"

SoundResourceManager::SoundResourceManager(uint16_t aSetIndex)
{
}

void SoundResourceManager::LoadByID(int16_t aID, std::string& aName)
{
    if (aID >= 0x40)
        return;

    // TODO: Load Sound
}
