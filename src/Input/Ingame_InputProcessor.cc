#include "Input/Ingame_InputProcessor.hpp"

Ingame_InputProcessor::Ingame_InputProcessor(SaveManager* aSaveManager)
    : InputProcessorBase()
{
    /*
    cPtr = &this->player1keyBindingData[2];
    saveRef = &aSaveManager->rawSaveData[494];    // Load keybinds from save data
    playerID = 2;
    do
    {
        ++cPtr;
        firstIndex = *((_WORD *)saveRef - 1);
        saveRef += 16;
        *(cPtr - 3) = InputProcessor_KeyCodes[firstIndex];
        *(cPtr - 1) = InputProcessor_KeyCodes[*((unsigned __int16 *)saveRef - 8)];
        cPtr[1] = InputProcessor_KeyCodes[*((unsigned __int16 *)saveRef - 7)];
        cPtr[3] = InputProcessor_KeyCodes[*((unsigned __int16 *)saveRef - 6)];
        cPtr[5] = InputProcessor_KeyCodes[*((unsigned __int16 *)saveRef - 5)];
        cPtr[7] = InputProcessor_KeyCodes[*((unsigned __int16 *)saveRef - 4)];
        cPtr[9] = InputProcessor_KeyCodes[*((unsigned __int16 *)saveRef - 3)];
        --playerID;
        cPtr[11] = InputProcessor_KeyCodes[*((unsigned __int16 *)saveRef - 2)];
    }
    while ( playerID );
    */
}

Ingame_InputProcessor::~Ingame_InputProcessor()
{
}

void Ingame_InputProcessor::Process()
{
    // TODO: Implement 00412DF0
}
