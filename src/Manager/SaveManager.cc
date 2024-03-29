#include <string.h>
#include <cstdio>
#include "Manager/SaveManager.hpp"

SaveManager::SaveManager()
{
    this->nextStage = 0;
    this->nextLevel = 0;
    this->saveFlags = 0;
    this->lastStageStatus = 0;
    this->dwordC = 0;

    FILE* saveFile = fopen("bpfdat.dat", "rb");

    if (saveFile != nullptr)
    {
        fread(&this->saveState, sizeof(this->saveState), 1, saveFile);
        fclose(saveFile);

        // TODO: Validate save data
    }
    else
    {
        this->saveState = SaveState();
    }

    this->CreatePlayerObjects();
}

SaveManager::~SaveManager()
{
    // TODO: This is the original logic of the game but it does not seem reliable, improve?
    FILE* saveFile = fopen("bpfdat.dat", "wb");

    if (saveFile != nullptr)
    {
        fwrite(&this->saveState, sizeof(this->saveState), 1, saveFile);
        fclose(saveFile);
    }
}

void SaveManager::CreatePlayerObjects()
{
    this->playerObject1.Initialize();
    this->playerObject2.Initialize();
}

bool SaveManager::Is2PMode()
{
    return this->IsFlagMaskEnabledAny(0x202);
}

uint32_t SaveManager::GetPlayerCount()
{
    return 1 + (this->Is2PMode());
}

uint16_t SaveManager::GetNextLevel()
{
    if (this->IsSecretMode())
        return 6;
    else
        return this->nextLevel;
}

bool SaveManager::IsSecretMode()
{
    return this->IsFlagMaskEnabledAny(0x200);
}

bool SaveManager::IsFlagMaskEnabledAny(uint32_t mask)
{
    return (this->saveFlags & mask) != 0;
}

bool SaveManager::IsFlagMaskEnabledAll(uint32_t mask)
{
    return (this->saveFlags & mask) == mask;
}

void SaveManager::SetControlKey(uint16_t isPlayerTwo, uint16_t keyIndex, uint16_t lastButtonPressed)
{
    if (lastButtonPressed < 0x32)
    {
        if (isPlayerTwo == 0)
        {
            this->saveState.p1Bindings[keyIndex] = lastButtonPressed;
        }
        else
        {
            this->saveState.p2Bindings[keyIndex] = lastButtonPressed;
        }
    }
}

Save_PlayerObject::Save_PlayerObject()
{
}

void Save_PlayerObject::Initialize()
{
    this->characterSelected = -1;
    this->score = 0;
    this->heartsLeft = 8;
}

ScoreboardEntry::ScoreboardEntry()
{
    this->character = 0;
    this->padding1 = 0;

    // "D.YAMA" indexes in MOJI font
    this->name[0] = 13; // D
    this->name[1] = 36; // .
    this->name[2] = 34; // Y
    this->name[3] = 10; // A
    this->name[4] = 22; // M
    this->name[5] = 10; // A
    this->name[6] = 37;
    this->name[7] = 37;

    this->a3 = 0;
    this->score = 100000;
}

SaveState::SaveState()
{
    // Default save state
    this->magic = 0x31465042; // "BPF1" in little endian

    for (int i = 0; i < 10; i++)
    {
        this->p1Scoreboard[i].character = (i % 2 == 0) ? 0 : 1;
        this->p1Scoreboard[i].score = 100000 - (10000 * i);

        this->p2Scoreboard[i].character = (i % 2 == 0) ? 0 : 1;
        this->p2Scoreboard[i].score = 100000 - (10000 * i);
    }

    this->nextStageIndex = 0;
    this->unk1 = 0;
    this->unk2 = 10;

    this->LoadDefaultKeyBindings();
}

void SaveState::LoadDefaultKeyBindings()
{
    // Default keybindings
    this->p1Bindings[0] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_E);
    this->p1Bindings[1] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_R);
    this->p1Bindings[2] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_W);
    this->p1Bindings[3] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_Q);
    this->p1Bindings[4] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_F);
    this->p1Bindings[5] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_V);
    this->p1Bindings[6] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_C);
    this->p1Bindings[7] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_B);

    this->p2Bindings[0] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_KP_COLON);
    this->p2Bindings[1] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_RIGHTBRACKET);
    this->p2Bindings[2] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_SEMICOLON);
    this->p2Bindings[3] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_L);
    this->p2Bindings[4] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_UP);
    this->p2Bindings[5] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_DOWN);
    this->p2Bindings[6] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_LEFT);
    this->p2Bindings[7] = InputKeyCodes::GetIndexForKeycode(SDL_SCANCODE_RIGHT);
}
