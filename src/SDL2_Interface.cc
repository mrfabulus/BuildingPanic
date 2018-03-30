#include "SDL2_Interface.hpp"

namespace sdl2
{
    SDL2_Interface::SDL2_Interface()
    {
        _initialized = (SDL_Init(SDL_INIT_EVERYTHING) == 0);
        nextFrameDrawTime = 0;
    }

    SDL2_Interface::~SDL2_Interface()
    {
        SDL_Quit();
        _initialized = false;
    }

    bool SDL2_Interface::isInitialized()
    {
        return _initialized;
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

    bool SDL2_Interface::InitializeRenderer()
    {
        gameRenderer = sdl2::make_renderer(gameWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (gameRenderer.get() == nullptr)
        {
            cout << "Error creating renderer: " << SDL_GetError() << endl;
            return false;
        }

        return true;
    }

    void SDL2_Interface::PerformEmptyBackSurfaceBlt()
    {
        SDL_RenderClear(gameRenderer.get());
    }

    bool SDL2_Interface::Flip()
    {
        while(false)
        {
            if (nextFrameDrawTime - 0 > 16)
                nextFrameDrawTime = 0;
        }

        // TODO: Check for errors
        SDL_RenderPresent(gameRenderer.get());
        nextFrameDrawTime = 0 + 16;
        return true;
    }

    SDL_Renderer* SDL2_Interface::GetRenderer()
    {
        return this->gameRenderer.get();
    }
}