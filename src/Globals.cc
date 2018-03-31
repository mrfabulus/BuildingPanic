#include "Globals.hpp"

sdl2::SDL2_Interface gSys;
GameManager* gGameManager;
bool gGameloopActive = true;
bool gNonStandardDimensions = true;

const uint16_t gConsts::referenceToSceneID_Linker[] =
{
    GameSceneID_Logo,
    GameSceneID_Menu,
    GameSceneID_Demoplay,
    GameSceneID_CharacterChoice,
    GameSceneID_Scoreboard,
    GameSceneID_StageStatus,
    GameSceneID_AfterGameCredits,
    GameSceneID_Ingame_Stage1,
    GameSceneID_Ingame_Stage2,
    GameSceneID_Ingame_Stage3,
    GameSceneID_Ingame_Stage4,
    GameSceneID_Ingame_Stage5
};

SDL_Rect MSRect::ToSDLRect()
{
    SDL_Rect result;
    result.x = this->left;
    result.y = this->top;
    result.w = this->right - this->left;
    result.h = this->bottom - this->top;
    return result;
}
