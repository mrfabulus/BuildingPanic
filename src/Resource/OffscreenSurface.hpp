#pragma once

#include <cstdint>

class Bitmap;
class SDL_Surface;
class MSRect;

class OffscreenSurface
{
    public:
        SDL_Surface* surface;
        Bitmap* bitmapPtr;
        uint32_t refCount;

        OffscreenSurface(Bitmap* aBitmap);
        virtual ~OffscreenSurface();

        virtual void Render(MSRect* aSrcRect, MSRect* aDstRect);

        void SetupSurface();
        void DecRefCount();
};
