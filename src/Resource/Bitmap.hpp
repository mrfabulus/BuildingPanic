#pragma once

#include <string>
#include "Globals.hpp"
#include "SDL2_Interface.hpp"

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

        // ---- NEW FIELDS FOR SDL SUPPORT ----
        SDL_Surface* SDL_surface;
        SDL_Texture* SDL_texture;
        char* filePath;

        // ---- Functions ----
        Bitmap(std::string& aName, void* ddPalette, int16_t aID, bool initialRefCount);
        ~Bitmap();

        void IncRefCount();
        void DecRefCount();

        void Render(MSRect* srcRect, MSRect* dstRect);
};
