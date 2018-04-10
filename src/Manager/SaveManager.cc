#include "SaveManager.hpp"
#include <string.h>

SaveManager::SaveManager()
{
    this->nextStage = 0;
    this->nextLevel = 0;
    this->saveFlags = 0;
    this->lastStageStatus = 0;
    this->dwordC = 0;

    // TODO: Read save data from file or create it in memory
    memset(&this->rawSaveData, 0, sizeof(this->rawSaveData));

    this->CreatePlayerObjects();
}

void SaveManager::CreatePlayerObjects()
{
    this->playerObject1.Initialize();
    this->playerObject2.Initialize();
}

Save_PlayerObject::Save_PlayerObject()
{
}

void Save_PlayerObject::Initialize()
{
    this->isPlayerControlled = -1;
    this->dword4 = 0;
    this->word8 = 8;
}