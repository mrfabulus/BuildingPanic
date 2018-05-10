#pragma once

#include <cstdint>

class Bitmap;
class SDL_Surface;
class MSRect;

class BitmapCacheSurface
{
    public:
        SDL_Surface* surface;
        Bitmap* bitmapPtr;
        uint32_t refCount;

        BitmapCacheSurface(Bitmap* aBitmap);
        virtual ~BitmapCacheSurface();

        virtual void Render(MSRect* aSrcRect, MSRect* aDstRect);

        void SetupSurface();
        void DecRefCount();
};
