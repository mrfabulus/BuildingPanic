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
    // TODO: Implement 00412DF0
}
