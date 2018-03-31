#pragma once

#include "SDL2_Interface.hpp"
#include <cstdint>

class GameManager;

struct gConsts
{
    static const uint16_t referenceToSceneID_Linker[];
};

class MSRect
{
    public:
        int32_t left;
        int32_t top;
        int32_t right;
        int32_t bottom;

        SDL_Rect ToSDLRect();
};

enum GameSceneID
{
    GameSceneID_Logo = 0,
    GameSceneID_Menu = 1,
    GameSceneID_Demoplay  = 2,
    GameSceneID_CharacterChoice  = 3,
    GameSceneID_Scoreboard  = 4,
    GameSceneID_StageStatus  = 5,
    GameSceneID_AfterGameCredits  = 6,
    GameSceneID_Ingame_Stage1  = 0x10,
    GameSceneID_Ingame_Stage2  = 0x11,
    GameSceneID_Ingame_Stage3  = 0x12,
    GameSceneID_Ingame_Stage4  = 0x13,
    GameSceneID_Ingame_Stage5  = 0x14
};

extern sdl2::SDL2_Interface gSys;
extern GameManager* gGameManager;
extern bool gGameloopActive;
extern bool gNonStandardDimensions;
