#include "LevelManager_base.hpp"
#include <string.h>

LevelManager_base::LevelManager_base(Ingame_BasicStage_Scene *aScene)
{
    this->Scene = aScene;
    memset(this->enemyFactories, 0, sizeof(this->enemyFactories));
}

LevelManager_base::~LevelManager_base()
{
}
