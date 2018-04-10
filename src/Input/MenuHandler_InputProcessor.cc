#include "MenuHandler_InputProcessor.hpp"
#include "../SDL2_Interface.hpp"

MenuHandler_InputProcessor::MenuHandler_InputProcessor()
    : InputProcessorBase()
{
    this->word14 = -1;
    this->dword18 = 0;
    this->dword1C = 0;
    this->dword20 = 0;
}

MenuHandler_InputProcessor::~MenuHandler_InputProcessor()
{
}

void MenuHandler_InputProcessor::Process()
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RETURN])
    {
        this->inputMask |= 1;
        this->inputMask |= 0x10000;
        // std::cout << "RETURN ";
    }

    if (state[SDL_SCANCODE_BACKSPACE])
    {
        this->inputMask |= 2;
        this->inputMask |= 0x20000;
        // std::cout << "BACKSPACE ";
    }

    if (state[SDL_SCANCODE_LEFT])
    {
        this->inputMask |= 0x10;
        this->inputMask |= 0x100000;
        // std::cout << "LEFT ";
    }

    if (state[SDL_SCANCODE_RIGHT])
    {
        this->inputMask |= 0x20;
        this->inputMask |= 0x200000;
        // std::cout << "RIGHT ";
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

    // TODO: Additional code from 00413120
}
