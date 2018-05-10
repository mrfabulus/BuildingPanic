#include <string.h>
#include "Manager/Level/LevelManager_Normal.hpp"

LevelManager_Normal::LevelManager_Normal(Ingame_BasicStage_Scene* aScene)
    : LevelManager_base(aScene)
{
    this->levelPhase = 0;
    this->dwordE4 = 0;
    this->dwordE8 = 0;
    this->dwordC4 = 0;
    this->dwordC8 = 0;
    this->dwordCC = 0;
    this->dwordD0 = 0;
    this->dwordD4 = 0;
    this->dwordD8 = 0;
    this->dwordDC = 0;
    this->wordE0 = 0;
    this->dword88 = 0;
    memset(this->buffer8C, 0, sizeof(this->buffer8C));

    // TODO: stuff
}

LevelManager_Normal::~LevelManager_Normal()
{
}

void LevelManager_Normal::F2()
{
}

void LevelManager_Normal::F3()
{
}

void LevelManager_Normal::F4()
{
}

void LevelManager_Normal::F5()
{
}

void LevelManager_Normal::F6()
{
}

void LevelManager_Normal::F7()
{
}

void LevelManager_Normal::F8()
{
}

void LevelManager_Normal::F9()
{
}
