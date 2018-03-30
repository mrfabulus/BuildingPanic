#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <iostream>

using namespace std;

// Very useful function from Eric Scott Barr.
// https://eb2.co/blog/2014/04/c-plus-plus-14-and-sdl2-managing-resources/
template <typename Creator, typename Destructor, typename... Arguments>
auto make_resource(Creator c, Destructor d, Arguments&&... args)
{
    auto r = c(std::forward<Arguments>(args)...);
    return std::unique_ptr<std::decay_t<decltype(*r)>, decltype(d)>(r, d);
}

namespace sdl2
{
    using window_ptr_t = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
    using renderer_ptr_t = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
    using surf_ptr_t = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
    using texture_ptr_t = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

    // Create a windows (unique_ptr with both a window and the destructor)
    inline window_ptr_t make_window(const char* title, int x, int y, int w, int h, Uint32 flags)
    {
        return make_resource(SDL_CreateWindow, SDL_DestroyWindow, title, x, y, w, h, flags);
    }

    // Create a renderer given a window, containing both the renderer and the destructor
    inline renderer_ptr_t make_renderer(SDL_Window* win, int x, Uint32 flags)
    {
        return make_resource(SDL_CreateRenderer, SDL_DestroyRenderer, win, x, flags);
    }

    // Create a surface from a bmp file, containing both the surface and the destructor
    inline surf_ptr_t make_bmp(SDL_RWops* sdlfile)
    {
        // May throw an exception if sdlfile is nullptr
        return make_resource(SDL_LoadBMP_RW, SDL_FreeSurface, sdlfile, 1);
    }

    // Create a texture from a renderer and a surface
    inline texture_ptr_t make_texture(SDL_Renderer* ren, SDL_Surface* surf)
    {
        return make_resource(SDL_CreateTextureFromSurface, SDL_DestroyTexture, ren, surf);
    }

    class SDL2_Interface
    {
        private:
            bool videoInit = false;
            window_ptr_t gameWindow = window_ptr_t(nullptr, nullptr);
            renderer_ptr_t gameRenderer = renderer_ptr_t(nullptr, nullptr);

            int nextFrameDrawTime;

        public:
            SDL2_Interface();
            ~SDL2_Interface();

            bool isVideoInitialized();
            bool SetupWindow();
            bool Initialize();

            void PerformEmptyBackSurfaceBlt();
            void Flip();

            SDL_Renderer* GetRenderer();
    };
}
