#pragma once

#include "InputProcessorBase.hpp"
#include <cstdint>

class SaveManager;

class Ingame_InputProcessor : public InputProcessorBase
{
    public:
        uint16_t player1keyBindingData[14];
        uint16_t player2keyBindingData[14];

        Ingame_InputProcessor(SaveManager* aSaveManager);
        ~Ingame_InputProcessor();

        virtual void Process() override;
};
