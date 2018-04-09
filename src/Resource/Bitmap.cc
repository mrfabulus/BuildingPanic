#include "Bitmap.hpp"
#include "../SDL2_Interface.hpp"
#include "../Globals.hpp"
#include <stdio.h>
#include <iostream>

#ifndef WIN32
#include <unistd.h>
#endif

Bitmap::Bitmap(std::string& aName, void* ddPalette, int16_t aID, bool initialRefCount)
{
    this->ddSurface = nullptr;
    this->ddPalette = ddPalette;
    this->refCount = 0;
    this->resourceName = aName;
    this->bufferMeta = nullptr;
    this->resourceID = aID;

    char* path = (char*) malloc(256);

    #ifdef WIN32
    snprintf(path, 256, "D:\\Building Panic\\BuildingPanic\\assets\\img\\%s.bmp", aName.c_str());
    #else
    snprintf(path, 256, "../assets/img/%s.bmp", aName.c_str());
    #endif

    #ifndef WIN32
    if( access( path, F_OK ) != -1 )
    {
        std::cout << "Bitmap creation OK for " << path << std::endl;
    }
    else
    {
        std::cout << "Bitmap creation ERROR for " << path << std::endl;
    }
    #endif

    // TODO: Handle errors gracefully
    this->SDL_handle = SDL_RWFromFile(path, "rb");

    if (initialRefCount)
    {
        this->incRefCount();
    }
}

Bitmap::~Bitmap()
{
    this->SDL_handle->close(this->SDL_handle);

    if (this->refCount != 0)
    {
        SDL_DestroyTexture(this->SDL_texture);
        SDL_FreeSurface(this->SDL_surface);
    }
}

void Bitmap::incRefCount()
{
    if (this->refCount == 0)
    {
        std::cout << "Ref count inc, loading " << this->resourceName << std::endl;

        // We have to create another surface to convert the image to our own format to satisfy blits
        SDL_Surface* otherSurf = nullptr;
        otherSurf = SDL_LoadBMP_RW(this->SDL_handle, 1);

        this->SDL_surface = gSys.CreateSurface(otherSurf->w, otherSurf->h);
        SDL_BlitSurface(otherSurf, NULL, this->SDL_surface, NULL);
        SDL_FreeSurface(otherSurf);

        this->SDL_texture = SDL_CreateTextureFromSurface(gSys.GetRenderer(), this->SDL_surface);

        // Set transparent color key to black
        SDL_SetColorKey(this->SDL_surface, SDL_TRUE, SDL_MapRGB(this->SDL_surface->format, 0, 0, 0));
    }

    this->refCount++;
}

void Bitmap::decRefCount()
{
    this->refCount--;

    if (this->refCount == 0)
    {
        SDL_DestroyTexture(this->SDL_texture);
        SDL_FreeSurface(this->SDL_surface);
    }
}

// TODO: Find out how to "Blit" textures so we can use VRAM
void Bitmap::Render(MSRect* srcRect, MSRect* dstRect)
{
    // Manual conversion from MS style rects into SDL style
    SDL_Rect SDL_srcRect = srcRect->ToSDLRect();
    SDL_Rect SDL_dstRect = dstRect->ToSDLRect();

    // SDL_RenderCopy(gSys.GetRenderer(), this->SDL_texture, &SDL_srcRect, &SDL_dstRect);
    SDL_BlitSurface(this->SDL_surface, &SDL_srcRect, gSys.GetMainSurface(), &SDL_dstRect);
}
