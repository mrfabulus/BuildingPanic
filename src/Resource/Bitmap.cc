#include "Bitmap.hpp"
#include "../SDL2_Interface.hpp"
#include "../Globals.hpp"
#include <stdio.h>
#include <unistd.h>
#include <iostream>

Bitmap::Bitmap(std::string& aName, void* ddPalette, int16_t aID, bool initialRefCount)
{
    this->ddSurface = nullptr;
    this->ddPalette = ddPalette;
    this->refCount = 0;
    this->resourceName = aName;
    this->bufferMeta = nullptr;
    this->resourceID = aID;

    char* path = (char*) malloc(256);
    snprintf(path, 256, "../assets/img/%s.bmp", aName.c_str());

    if( access( path, F_OK ) != -1 )
    {
        std::cout << "Bitmap creation OK for " << path << std::endl;
    }
    else
    {
        std::cout << "Bitmap creation ERROR for " << path << std::endl;
    }

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
}

void Bitmap::incRefCount()
{
    if (this->refCount == 0)
    {
        std::cout << "Ref count inc, loading " << this->resourceName << std::endl;
        this->SDL_surface = SDL_LoadBMP_RW(this->SDL_handle, 1);
        this->SDL_texture = SDL_CreateTextureFromSurface(gSys.GetRenderer(), this->SDL_surface);
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

void Bitmap::Render(MSRect* srcRect, MSRect* dstRect)
{
    // Manual conversion from MS style rects into SDL style
    SDL_Rect SDL_srcRect = srcRect->ToSDLRect();
    SDL_Rect SDL_dstRect = dstRect->ToSDLRect();

    SDL_RenderCopy(gSys.GetRenderer(), this->SDL_texture, &SDL_srcRect, &SDL_dstRect);
}