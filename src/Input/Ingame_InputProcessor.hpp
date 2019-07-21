#pragma once

#include <cstdint>
#include "Input/InputProcessorBase.hpp"

class SaveManager;

class Ingame_InputProcessor : public InputProcessorBase
{
    public:
        SDL_Scancode player1keyBindingData[8];
        SDL_Scancode player2keyBindingData[8];

        Ingame_InputProcessor(SaveManager* aSaveManager);
        ~Ingame_InputProcessor();

        virtual void Process() override;
};
