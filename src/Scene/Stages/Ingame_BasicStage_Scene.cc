#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"
#include "Manager/SaveManager.hpp"
#include "Manager/Level/LevelManager_Normal.hpp"

Ingame_BasicStage_Scene::Ingame_BasicStage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager)
    : Ingame_Stage_Scene(aPaletteDataBytes, aSaveManager)
{
    LevelManager_base* managerObject = nullptr;

    // Check demoplay flag
    if (((this->saveManager->saveFlags >> 8) & 0x10) == 0)
    {
        // TODO: Create LevelManager_Demoplay
    }
    else if ((this->saveManager->saveFlags & 0x200) != 0)
    {
        // TODO: Create LevelManager_Secret
    }
    else if (this->saveManager->nextLevel == 2)
    {
        // TODO: Create LevelManager_BonusLevel
    }
    else if (this->saveManager->nextLevel == 5)
    {
        // TODO: Create LevelManager_BossLevel
    }
    else
    {
        managerObject = new LevelManager_Normal(this);
    }

    this->levelManagerObject = managerObject;
}

Ingame_BasicStage_Scene::~Ingame_BasicStage_Scene()
{
    // TODO: Stop midi

    if (this->levelManagerObject != nullptr)
    {
        delete this->levelManagerObject;
        this->levelManagerObject = nullptr;
    }
}
