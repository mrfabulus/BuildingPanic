#pragma once

#include <cstdint>

class Save_PlayerObject
{
    private:
        int8_t isPlayerControlled;
        int32_t dword4;
        int16_t word8;
    public:
        Save_PlayerObject();

        void Initialize();
};

class SaveManager
{
    // private:
    public:
        uint16_t nextStage;
        int16_t nextLevel;
        int16_t saveFlags;
        int16_t lastStageStatus;
        int32_t dwordC;
        int32_t gap10;
        int32_t field_14;
        Save_PlayerObject playerObject1;
        Save_PlayerObject playerObject2;
        int8_t rawSaveData[524];
    // public:
        SaveManager();

        void CreatePlayerObjects();
};
