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

Save_PlayerObject::Save_PlayerObject()
{
}

void Save_PlayerObject::Initialize()
{
    this->characterSelected = -1;
    this->dword4 = 0;
    this->heartsLeft = 8;
}

ScoreboardEntry::ScoreboardEntry()
{
    this->character = 0;
    this->padding1 = 0;

    // "D. YAMA" bytes somehow??
    this->name[0] = 13;
    this->name[1] = 36;
    this->name[2] = 34;
    this->name[3] = 10;
    this->name[4] = 22;
    this->name[5] = 10;
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

    this->stagesCompleted = 0;
    this->unk1 = 0;
    this->unk2 = 10;

    // Default keybindings
    this->player1Bindings[0] = 0x0E;
    this->player1Bindings[1] = 0x1B;
    this->player1Bindings[2] = 0x20;
    this->player1Bindings[3] = 0x1A;
    this->player1Bindings[4] = 0x0F;
    this->player1Bindings[5] = 0x1F;
    this->player1Bindings[6] = 0x0C;
    this->player1Bindings[7] = 0x0B;

    this->player2Bindings[0] = 0x28;
    this->player2Bindings[1] = 0x29;
    this->player2Bindings[2] = 0x27;
    this->player2Bindings[3] = 0x15;
    this->player2Bindings[4] = 0x2E;
    this->player2Bindings[5] = 0x2F;
    this->player2Bindings[6] = 0x30;
    this->player2Bindings[7] = 0x31;
}
