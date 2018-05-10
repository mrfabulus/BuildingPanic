#pragma once

#include <cstdint>
#include "Input/InputProcessorBase.hpp"

class SaveManager;

class Ingame_InputProcessor : public InputProcessorBase
{
    public:
        uint16_t player1keyBindingData[8];
        uint16_t player2keyBindingData[8];

        Ingame_InputProcessor(SaveManager* aSaveManager);
        ~Ingame_InputProcessor();

        virtual void Process() override;
};
