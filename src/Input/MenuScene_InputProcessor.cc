#include <iostream>
#include "SDL2_Interface.hpp"
#include "Input/MenuScene_InputProcessor.hpp"

MenuScene_InputProcessor::MenuScene_InputProcessor()
    : InputProcessorBase()
{
    this->word14 = -1;
}

MenuScene_InputProcessor::~MenuScene_InputProcessor()
{
}

void MenuScene_InputProcessor::Process()
{
    // std::cout << "MenuScene_InputProcessor::Process ";
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RETURN])
    {
        this->inputMask |= 1;
        this->inputMask |= 0x10000;
        // std::cout << "RETURN ";
    }

    if (state[SDL_SCANCODE_UP])
    {
        this->inputMask |= 0x40;
        this->inputMask |= 0x400000;
        // std::cout << "UP ";
    }

    if (state[SDL_SCANCODE_DOWN])
    {
        this->inputMask |= 0x80;
        this->inputMask |= 0x800000;
        // std::cout << "DOWN ";
    }

    // std::cout << std::endl;
}
