#pragma once

#include "../Resource/Bitmap.hpp"
#include <cstdint>

class BitmapResourceManager
{
    public:
        Bitmap* bitmapPtrs[128];
        // BitmapPairObject *bitmapPairObjectPtrs[128];
        void* bitmapPairObjectPtrs[128];

        // LPDIRECTDRAWPALETTE ddPalette;
        void* ddPalette;

        BitmapResourceManager(uint16_t setID, void* ddPalette, uint16_t secondSetID);

        void LoadBySetID(uint16_t setID);
};
