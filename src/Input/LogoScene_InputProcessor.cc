#include "LogoScene_InputProcessor.hpp"
#include "../SDL2_Interface.hpp"

LogoScene_InputProcessor::LogoScene_InputProcessor()
    : InputProcessorBase()
{
}

LogoScene_InputProcessor::~LogoScene_InputProcessor()
{
}

void LogoScene_InputProcessor::Process()
{
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_P])
    {
        this->inputMask |= 1;
    }

    if (state[SDL_SCANCODE_A])
    {
        this->inputMask |= 2;
    }

    if (state[SDL_SCANCODE_N])
    {
        this->inputMask |= 4;
    }

    if (state[SDL_SCANCODE_I])
    {
        this->inputMask |= 8;
    }

    if (state[SDL_SCANCODE_C])
    {
        this->inputMask |= 16;
    }
}
