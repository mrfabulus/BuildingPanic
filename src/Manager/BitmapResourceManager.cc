#include "BitmapResourceManager.hpp"
#include <string.h>

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
    // TODO: Add loading logic
}
