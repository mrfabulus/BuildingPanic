#pragma once

#include <cstdint>
#include "SDL2_Interface.hpp"

class Save_PlayerObject
{
    public:
        int8_t characterSelected; // 0 for Doka, 1 for Tobi
        int32_t score;
        int16_t heartsLeft;

        Save_PlayerObject();

        void Initialize();
};

class ScoreboardEntry
{
    public:
        uint8_t character; // 0 for Doka, 1 for Tobi
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
        uint16_t nextStageIndex;
        uint16_t unk1;
        int32_t unk2;
        uint16_t p1Bindings[8];
        uint16_t p2Bindings[8];

        SaveState();
        void LoadDefaultKeyBindings();
};

class SaveManager
{
    public:
        uint16_t nextStage;
        uint16_t nextLevel;
        uint16_t saveFlags;
        uint16_t lastStageStatus;
        uint32_t dwordC;
        uint32_t dword10;
        uint32_t dword14;

        Save_PlayerObject playerObject1;
        Save_PlayerObject playerObject2;
        SaveState saveState;

        SaveManager();
        virtual ~SaveManager();

        void CreatePlayerObjects();
        bool Is2PMode();
        uint32_t GetPlayerCount();
        uint16_t GetNextLevel();
        bool IsSecretMode();
        bool IsFlagMaskEnabledAny(uint32_t mask);
        bool IsFlagMaskEnabledAll(uint32_t mask);

        void SetControlKey(uint16_t isPlayerTwo, uint16_t keyIndex, uint16_t lastButtonPressed);
};
