#include <string.h>
#include "Manager/Level/LevelManager_base.hpp"

LevelManager_base::LevelManager_base(Ingame_BasicStage_Scene *aScene)
{
    this->scene = aScene;
    memset(this->enemyFactories, 0, sizeof(this->enemyFactories));
}

LevelManager_base::~LevelManager_base()
{
}

bool LevelManager_base::F7()
{
    return false;
}
