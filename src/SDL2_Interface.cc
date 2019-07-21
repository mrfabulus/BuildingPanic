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

/*
DIK_0, DIK_1, DIK_2, DIK_3, DIK_4, DIK_5, DIK_6, DIK_7
DIK_8, DIK_9, DIK_A, DIK_B, DIK_C, DIK_D, DIK_E, DIK_F
DIK_G, DIK_H, DIK_I, DIK_J, DIK_K, DIK_L, DIK_M, DIK_N
DIK_O, DIK_P, DIK_Q, DIK_R, DIK_S, DIK_T, DIK_U, DIK_V
DIK_W, DIK_X, DIK_Y, DIK_Z, DIK_MINUS, DIK_AT, DIK_LBRACKET
DIK_SEMICOLON, DIK_COLON, DIK_RBRACKET, DIK_COMMA, DIK_PERIOD
DIK_SLASH, DIK_BACKSLASH, DIK_UP, DIK_DOWN, DIK_LEFT
DIK_RIGHT
*/

const SDL_Scancode InputKeyCodes::keyCodeArray[] =
{
    SDL_SCANCODE_0, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3,
    SDL_SCANCODE_4, SDL_SCANCODE_5, SDL_SCANCODE_6, SDL_SCANCODE_7,
    SDL_SCANCODE_8, SDL_SCANCODE_9, SDL_SCANCODE_A, SDL_SCANCODE_B,
    SDL_SCANCODE_C, SDL_SCANCODE_D, SDL_SCANCODE_E, SDL_SCANCODE_F,
    SDL_SCANCODE_G, SDL_SCANCODE_H, SDL_SCANCODE_I, SDL_SCANCODE_J,
    SDL_SCANCODE_K, SDL_SCANCODE_L, SDL_SCANCODE_M, SDL_SCANCODE_N,
    SDL_SCANCODE_O, SDL_SCANCODE_P, SDL_SCANCODE_Q, SDL_SCANCODE_R,
    SDL_SCANCODE_S, SDL_SCANCODE_T, SDL_SCANCODE_U, SDL_SCANCODE_V,
    SDL_SCANCODE_W, SDL_SCANCODE_X, SDL_SCANCODE_Y, SDL_SCANCODE_Z,
    // I'm really confused about this part, the original keycode array does not have a caret symbol
    // However, the MOJI png render structure does, and yet the render code uses the indexes from this array in the render structure
    SDL_SCANCODE_MINUS, SDL_SCANCODE_UNKNOWN /* SDLK_CARET */, SDL_SCANCODE_KP_AT, SDL_SCANCODE_LEFTBRACKET,
    SDL_SCANCODE_SEMICOLON, SDL_SCANCODE_KP_COLON, SDL_SCANCODE_RIGHTBRACKET,
    SDL_SCANCODE_COMMA, SDL_SCANCODE_PERIOD, SDL_SCANCODE_SLASH, SDL_SCANCODE_BACKSLASH,
    SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT
};

uint16_t InputKeyCodes::GetIndexForKeycode(SDL_Scancode keycode)
{
    const SDL_Scancode* keyCodeBasePtr = &InputKeyCodes::keyCodeArray[0];
    uint32_t keyCodeArrayLength = sizeof(InputKeyCodes::keyCodeArray) / sizeof(SDL_Scancode);

    uint16_t currentButtonIndex = 0;

    for (; currentButtonIndex <= keyCodeArrayLength; currentButtonIndex++)
    {
        if (currentButtonIndex == keyCodeArrayLength)
        {
            currentButtonIndex = -1;
            break;
        }

        SDL_Scancode currentKey = *(keyCodeBasePtr + currentButtonIndex);

        if (currentKey == keycode)
        {
            break;
        }
    }

    return currentButtonIndex;
}

uint16_t InputKeyCodes::GetIndexForPressedKey(const uint8_t* state)
{
    const SDL_Scancode* keyCodeBasePtr = &InputKeyCodes::keyCodeArray[0];
    uint32_t keyCodeArrayLength = sizeof(InputKeyCodes::keyCodeArray) / sizeof(SDL_Scancode);

    uint16_t currentButtonIndex = 0;

    for (; currentButtonIndex <= keyCodeArrayLength; currentButtonIndex++)
    {
        if (currentButtonIndex == keyCodeArrayLength)
        {
            currentButtonIndex = -1;
            break;
        }

        SDL_Scancode currentKey = *(keyCodeBasePtr + currentButtonIndex);

        if (state[currentKey] != 0)
        {
            break;
        }
    }

    return currentButtonIndex;
}

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
