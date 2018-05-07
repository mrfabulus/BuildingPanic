#pragma once

#include <string>
#include "../SDL2_Interface.hpp"
#include "../Globals.hpp"

class Bitmap
{
    public:
        // ---- ORIGINAL FIELDS ----
        // LPDIRECTDRAWSURFACE7 ddSurface;
        void* ddSurface;
        // LPDIRECTDRAWPALETTE ddPalette;
        void* ddPalette;

        int refCount;
        std::string resourceName;

        // Bitmap_BufferMeta *bufferMeta;
        void* bufferMeta;

        // DDBLTFX bltfx;

        int resourceID;

        // ---- NEW FIELD FOR SDL ----
        SDL_Surface* SDL_surface;
        SDL_Texture* SDL_texture;
        char* filePath;

        // ---- Functions ----
        Bitmap(std::string& aName, void* ddPalette, int16_t aID, bool initialRefCount);
        ~Bitmap();

        void incRefCount();
        void decRefCount();

        void Render(MSRect* srcRect, MSRect* dstRect);
};
