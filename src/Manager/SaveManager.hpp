#pragma once

class Save_PlayerObject
{
    private:
        char isPlayerControlled;
        int dword4;
        short word8;
    public:
        Save_PlayerObject()
        {
        }

        void Initialize()
        {
            this->isPlayerControlled = -1;
            this->dword4 = 0;
            this->word8 = 8;
        }
};

class SaveManager
{
    // private:
    public:
        uint16_t nextStage;
        short nextLevel;
        short saveFlags;
        short lastStageStatus;
        int dwordC;
        int gap10;
        int field_14;
        Save_PlayerObject playerObject1;
        Save_PlayerObject playerObject2;
        char rawSaveData[524];
    // public:
        SaveManager()
        {
            this->nextStage = 0;
            this->nextLevel = 0;
            this->saveFlags = 0;
            this->lastStageStatus = 0;
            this->dwordC = 0;

            // TODO: Read save data from file or create it in memory

            this->CreatePlayerObjects();
        }

        void CreatePlayerObjects()
        {
            this->playerObject1.Initialize();
            this->playerObject2.Initialize();
        }
};
