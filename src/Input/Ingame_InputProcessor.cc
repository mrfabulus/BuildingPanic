#include "Input/Ingame_InputProcessor.hpp"
#include "Manager/SaveManager.hpp"

Ingame_InputProcessor::Ingame_InputProcessor(SaveManager* aSaveManager)
    : InputProcessorBase()
{
    for (int i = 0; i < 8; i++)
        this->player1keyBindingData[i] = InputKeyCodes::keyCodeArray[aSaveManager->saveState.p1Bindings[i]];

    for (int i = 0; i < 8; i++)
        this->player2keyBindingData[i] = InputKeyCodes::keyCodeArray[aSaveManager->saveState.p2Bindings[i]];
}

Ingame_InputProcessor::~Ingame_InputProcessor()
{
}

void Ingame_InputProcessor::Process()
{
    const uint8_t* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_F2])
    {
        this->inputMask |= 2;
    }

    if (state[this->player1keyBindingData[6]])
    {
        this->inputMask |= 0x10;
    }

    if (state[this->player2keyBindingData[0]])
    {
        this->inputMask |= 0x20;
    }

    // Player 1 controls
    if (state[this->player1keyBindingData[4]])
    {
        this->inputMask |= 0x40;
    }

    if (state[this->player1keyBindingData[5]])
    {
        this->inputMask |= 0x80;
    }

    if (state[this->player1keyBindingData[0]])
    {
        this->inputMask |= 0x1000;
    }

    if (state[this->player1keyBindingData[1]])
    {
        this->inputMask |= 0x200;
    }

    if (state[this->player1keyBindingData[2]])
    {
        this->inputMask |= 0x400;
    }

    if (state[this->player1keyBindingData[3]])
    {
        this->inputMask |= 0x100;
    }

    // Player 2 controls
    /* The iteration is weird ...
    if (state[this->player1keyBindingData[4]])
    {
        this->inputMask |= 0x40;
    }

    if (state[this->player1keyBindingData[5]])
    {
        this->inputMask |= 0x80;
    }

    if (state[this->player1keyBindingData[0]])
    {
        this->inputMask |= 0x1000;
    }

    if (state[this->player1keyBindingData[1]])
    {
        this->inputMask |= 0x200;
    }

    if (state[this->player1keyBindingData[2]])
    {
        this->inputMask |= 0x400;
    }

    if (state[this->player1keyBindingData[3]])
    {
        this->inputMask |= 0x100;
    }
    */

}
