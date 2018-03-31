#include "Bitmap.hpp"
#include "../SDL2_Interface.hpp"
#include "../Globals.hpp"
#include <stdio.h>

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
    SDL_Rect SDL_srcRect;
    SDL_Rect SDL_dstRect;

    SDL_srcRect.x = srcRect->left;
    SDL_srcRect.y = srcRect->top;
    SDL_srcRect.w = srcRect->right - srcRect->left;
    SDL_srcRect.h = srcRect->bottom - srcRect->top;

    SDL_dstRect.x = dstRect->left;
    SDL_dstRect.y = dstRect->top;
    SDL_dstRect.w = dstRect->right - dstRect->left;
    SDL_dstRect.h = dstRect->bottom - dstRect->top;

    SDL_RenderCopy(gSys.GetRenderer(), this->SDL_texture, &SDL_srcRect, &SDL_dstRect);
}
