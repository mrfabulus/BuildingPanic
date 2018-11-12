#pragma once

#include <cstdint>
#include "Input/InputProcessorBase.hpp"
#include "SDL2_Interface.hpp"

class SaveManager;

struct InputKeyCodes
{
    static const SDL_Scancode keyCodeArray[50];
};

class Ingame_InputProcessor : public InputProcessorBase
{
    public:
        SDL_Scancode player1keyBindingData[8];
        SDL_Scancode player2keyBindingData[8];

        Ingame_InputProcessor(SaveManager* aSaveManager);
        ~Ingame_InputProcessor();

        virtual void Process() override;
};
