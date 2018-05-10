#pragma once

#include <cstdint>
#include <string>

class Bitmap;
class BitmapCacheSurface;

struct BitmapInformation
{
    static const std::string Names[];

    static const int16_t* LogoScene_ResourceLinkerPtr;
    static const int16_t* MenuScene_ResourceLinkerPtr;
    static const int16_t* CharacterChoice_ResourceLinkerPtr;
    static const int16_t* ScoreboardScene_ResourceLinkerPtr;
    static const int16_t* StageStatusScene_ResourceLinkerPtr;
    static const int16_t* AfterGameCreditsScene_ResourceLinkerPtr;
    static const int16_t* IngameStage1_ResourceLinkerPtr;
    static const int16_t* IngameStage2_ResourceLinkerPtr;
    static const int16_t* IngameStage3_ResourceLinkerPtr;
    static const int16_t* IngameStage4_ResourceLinkerPtr;
    static const int16_t* IngameStage5_ResourceLinkerPtr;
    static const int16_t* LooksSecretToMePtr;
};

class BitmapResourceManager
{
    public:
        Bitmap* bitmapPtrs[128];
        BitmapCacheSurface* bitmapPairObjectPtrs[128];

        // LPDIRECTDRAWPALETTE ddPalette;
        void* ddPalette;

        BitmapResourceManager(uint16_t setID, void* ddPalette, uint16_t secondSetID);
        virtual ~BitmapResourceManager();

        void LoadBySetID(uint16_t setID);
        void LoadByID(std::string& aName, int16_t aID);
};
