#pragma once

class Bitmap
{
    public:
        // LPDIRECTDRAWSURFACE7 ddSurface;
        // LPDIRECTDRAWPALETTE ddPalette;
        int refCount;
        char *resourceName;
        // Bitmap_BufferMeta *bufferMeta;
        // DDBLTFX bltfx;
        int resourceID;

        Bitmap();

        void incRefCount();
        void decRefCount();

};
