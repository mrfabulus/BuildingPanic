#pragma once

#include "SDL2_Interface.hpp"
#include <cstdint>

class GameManager;

extern sdl2::SDL2_Interface gSys;
extern GameManager* gGameManager;
extern bool gGameloopActive;
extern bool gNonStandardDimensions;

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
