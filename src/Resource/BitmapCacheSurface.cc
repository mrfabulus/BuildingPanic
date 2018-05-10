#include "Globals.hpp"
#include "SDL2_Interface.hpp"
#include "Resource/Bitmap.hpp"
#include "Resource/BitmapCacheSurface.hpp"

BitmapCacheSurface::BitmapCacheSurface(Bitmap* aBitmap)
{
    this->surface = nullptr;
    this->bitmapPtr = aBitmap;
    this->refCount = 0;
}

BitmapCacheSurface::~BitmapCacheSurface()
{
    if (this->surface != nullptr)
    {
        SDL_FreeSurface(this->surface);
        this->surface = nullptr;
    }
}

// TODO: Find out how to "Blit" textures so we can use VRAM
void BitmapCacheSurface::Render(MSRect* aSrcRect, MSRect* aDstRect)
{
    // Manual conversion from MS style rects into SDL style
    SDL_Rect SDL_srcRect = aSrcRect->ToSDLRect();
    SDL_Rect SDL_dstRect = aDstRect->ToSDLRect();

    // SDL_RenderCopy(gSys.GetRenderer(), this->SDL_texture, &SDL_srcRect, &SDL_dstRect);
    SDL_BlitSurface(this->surface, &SDL_srcRect, gSys.GetMainSurface(), &SDL_dstRect);
}

void BitmapCacheSurface::SetupSurface()
{
    // Create an exact copy of the associated bitmap's surface data
    this->surface = gSys.CreateSurface(this->bitmapPtr->SDL_surface->w, this->bitmapPtr->SDL_surface->h);
    SDL_BlitSurface(this->bitmapPtr->SDL_surface, nullptr, this->surface, nullptr);

    // Set transparent color key to black
    SDL_SetColorKey(this->surface, SDL_TRUE, SDL_MapRGB(this->surface->format, 0, 0, 0));
}

void BitmapCacheSurface::DecRefCount()
{
    this->refCount--;

    if (this->refCount == 0)
    {
        SDL_FreeSurface(this->surface);
        this->surface = nullptr;
    }
}
