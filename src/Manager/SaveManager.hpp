#pragma once

#include <cstdint>

class Save_PlayerObject
{
    public:
        int8_t characterSelected; // 0 for Doka, 1 for Tobi
        int32_t dword4;
        int16_t heartsLeft;

        Save_PlayerObject();

        void Initialize();
};

class ScoreboardEntry
{
    public:
        uint8_t character;
        uint8_t padding1;
        uint16_t name[8];
        uint16_t a3;
        uint32_t score;

        ScoreboardEntry();
};

class SaveState
{
    public:
        uint32_t magic;
        ScoreboardEntry p1Scoreboard[10];
        ScoreboardEntry p2Scoreboard[10];
        uint16_t stagesCompleted;
        uint16_t unk1;
        uint32_t unk2;
        uint16_t player1Bindings[8];
        uint16_t player2Bindings[8];

        SaveState();
};

class SaveManager
{
    public:
        uint16_t nextStage;
        uint16_t nextLevel;
        uint16_t saveFlags;
        uint16_t lastStageStatus;
        int32_t dwordC;
        int32_t gap10;
        int32_t field_14;
        Save_PlayerObject playerObject1;
        Save_PlayerObject playerObject2;
        SaveState saveState;

        SaveManager();
        virtual ~SaveManager();

        void CreatePlayerObjects();
};
