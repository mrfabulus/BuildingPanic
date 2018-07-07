#define _POSIX_C_SOURCE 200809L

#include "SDL2_Interface.hpp"
#include "Globals.hpp"
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

// TODO: Fix these...
#ifdef WIN32
#include "Windows.h"

long getTimeMS()
{
	// return timeGetTime();
	return 0;
}
#else
long getTimeMS()
{
    return 0;

    /*
    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    
    if (ms > 999)
    {
        s++;
        ms = 0;
    }

    return ms;
    */
}
#endif

namespace sdl2
{
    SDL2_Interface::SDL2_Interface()
    {
        videoInit = (SDL_Init(SDL_INIT_VIDEO) == 0);
        nextFrameDrawTime = 0;
    }

    SDL2_Interface::~SDL2_Interface()
    {
        Mix_CloseAudio();
        SDL_Quit();
    }

    bool SDL2_Interface::IsVideoInitialized()
    {
        return videoInit;
    }

    bool SDL2_Interface::SetupWindow()
    {
        gameWindow = sdl2::make_window("Building Panic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

        if (gameWindow.get() == nullptr)
        {
            cout << "Error creating window: " << SDL_GetError() << endl;
            return false;
        }

        return true;
    }

    bool SDL2_Interface::Initialize()
    {
        // Initialize subsystems other than video
        uint32_t subsystems = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_EVENTS;
        
        // TODO: Handle and init JOYSTICK, HAPTIC, GAMECONTROLLER

        if (SDL_Init(subsystems) != 0)
        {
            cout << "Error in further SDL initialization: " << SDL_GetError() << endl;
            return false;
        }

        gameRenderer = sdl2::make_renderer(gameWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (gameRenderer.get() == nullptr)
        {
            cout << "Error creating renderer: " << SDL_GetError() << endl;
            return false;
        }

        // Init 8 bit proxy
        this->proxyRenderSurface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);
        this->proxyRenderTexture = SDL_CreateTexture(gameRenderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

        /*int mix_flags = MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MOD;
        int mix_init = Mix_Init(mix_flags);
        if(mix_init & mix_flags != mix_flags)
        {
            printf("Mix_Init: Failed to init required ogg and mod support!\n");
            printf("Mix_Init: %s\n", Mix_GetError());
        }*/

        //22050, MIX_DEFAULT_FORMAT, 2, 4096
        //44100, MIX_DEFAULT_FORMAT, 2, 2048
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1 )
        {
            cout << "Error opening audio: " << Mix_GetError() << endl;
            return false;
        }

        return true;
    }

    void SDL2_Interface::PerformEmptyBackSurfaceBlt()
    {
        // SDL_RenderClear(gameRenderer.get());
        SDL_FillRect(this->proxyRenderSurface, NULL, SDL_MapRGB(this->proxyRenderSurface->format, 0, 0, 0));
    }

    void SDL2_Interface::Flip()
    {
        long cTime = getTimeMS();

        // If necessary, wait before pushing out the frame
        if (cTime < nextFrameDrawTime)
        {
            SDL_Delay(nextFrameDrawTime - cTime);
        }

        void *pixels;
        int pitch;

        // Take the pixels from proxyRenderSurface
        SDL_LockTexture(proxyRenderTexture, NULL, &pixels, &pitch);

        // Convert them into RGBA8888
        SDL_ConvertPixels(this->proxyRenderSurface->w, this->proxyRenderSurface->h,
            this->proxyRenderSurface->format->format,
            this->proxyRenderSurface->pixels, this->proxyRenderSurface->pitch,
            SDL_PIXELFORMAT_RGBA8888,
            pixels, pitch);

        // Store the result of the conversion into proxyRenderTexture
        SDL_UnlockTexture(this->proxyRenderTexture);

        // Clear the window's backbuffer
        SDL_RenderClear(gameRenderer.get());
        // Copy the created proxyRenderTexture onto the window's backbuffer
        SDL_RenderCopy(gameRenderer.get(), this->proxyRenderTexture, NULL, NULL);
        // Flip
        SDL_RenderPresent(gameRenderer.get());

        nextFrameDrawTime = cTime + 16;
    }

    SDL_Surface* SDL2_Interface::CreateSurface(uint32_t width, uint32_t height)
    {
        return SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    }

    SDL_Surface* SDL2_Interface::GetMainSurface()
    {
        // return SDL_GetWindowSurface(this->gameWindow.get());
        return this->proxyRenderSurface;
    }

    SDL_Renderer* SDL2_Interface::GetRenderer()
    {
        return this->gameRenderer.get();
    }

    void SDL2_Interface::ProcessEvents()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    gGameloopRunning = false;
                    break;
            }
        }
    }
}
