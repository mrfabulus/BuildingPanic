#pragma once

#include "../Resource/Bitmap.hpp"
#include <cstdint>
#include <string>

struct BitmapInformation
{
    static const std::string Names[];

    static const int16_t* LogoScene_ResourceLinkerPtr;
    static const int16_t* MenuScene_ResourceLinkerPtr;
    static const int16_t* CharacterChoice_ResourceLinkerPtr;
    static const int16_t* ScoreboardScene_ResourceLinkerPtr;
    static const int16_t* StageStatusScene_ResourceLinkerPtr;
    static const int16_t* AfterGameCreditsScene_ResourceLinkerPtr;
    static const int16_t* IngameStage1ResourceLinkerPtr;
    static const int16_t* IngameStage2ResourceLinkerPtr;
    static const int16_t* IngameStage3ResourceLinkerPtr;
    static const int16_t* IngameStage4ResourceLinkerPtr;
    static const int16_t* IngameStage5ResourceLinkerPtr;
    static const int16_t* LooksSecretToMePtr;
};

class BitmapResourceManager
{
    public:
        Bitmap* bitmapPtrs[128];
        // BitmapPairObject *bitmapPairObjectPtrs[128];
        void* bitmapPairObjectPtrs[128];

        // LPDIRECTDRAWPALETTE ddPalette;
        void* ddPalette;

        BitmapResourceManager(uint16_t setID, void* ddPalette, uint16_t secondSetID);

        void LoadBySetID(uint16_t setID);
        void LoadByID(std::string& aName, int16_t aID);
};
