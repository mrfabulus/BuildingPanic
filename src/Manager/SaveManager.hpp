#pragma once

#include <cstdint>

class Save_PlayerObject
{
    public:
        int8_t characterSelected; // 0 for Doka, 1 for Tobi
        int32_t dword4;
        int16_t word8; // hearts left (?)
    // public:
        Save_PlayerObject();

        void Initialize();
};

class SaveManager
{
    // private:
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
        uint8_t rawSaveData[524];

        static const uint8_t defaultSaveData[524];

    // public:
        SaveManager();
        ~SaveManager();

        void CreatePlayerObjects();
};
