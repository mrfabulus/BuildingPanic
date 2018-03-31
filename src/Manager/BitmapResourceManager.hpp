#pragma once

#include "../Resource/Bitmap.hpp"
#include <cstdint>
#include <string>

struct BitmapInformation
{
    static const std::string Names[];

    static const int16_t* LogoScene_ResourceLinkerPtr;
    static const int16_t* MenuScene_ResourceLinkerPtr;
    /*
    static const int16_t* CharacterChoice_ResourceLinkerPtr;
    static const int16_t* ScoreboardScene_ResourceLinkerPtr;
    static const int16_t* StageStatusScene_ResourceLinker;
    static const int16_t* AfterGameCreditsScene_ResourceLinker;
    static const int16_t* IngameStage1ResourceLinker;
    static const int16_t* IngameStage2ResourceLinker;
    static const int16_t* IngameStage3ResourceLinker;
    static const int16_t* IngameStage4ResourceLinker;
    static const int16_t* IngameStage5ResourceLinker;
    static const int16_t* LooksSecretToMe;
    */
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
