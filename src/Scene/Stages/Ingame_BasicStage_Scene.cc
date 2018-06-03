#include "Scene/Stages/Ingame_BasicStage_Scene.hpp"
#include "Manager/SaveManager.hpp"
#include "Manager/Level/LevelManager_Normal.hpp"

Ingame_BasicStage_Scene::Ingame_BasicStage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager)
    : Ingame_Stage_Scene(aPaletteDataBytes, aSaveManager)
{
    LevelManager_base* managerObject = nullptr;
    printf("Ingame_BasicStage_Scene::ctor\n");

    // Check demoplay flag
    /*if (((this->saveManager->saveFlags >> 8) & 0x10) == 0)
    {
        printf("Ingame_BasicStage_Scene Demoplay\n");
        // TODO: Create LevelManager_Demoplay
    }
    else */ if (this->saveManager->IsSecretMode())
    {
        printf("Ingame_BasicStage_Scene Secret mode\n");
        // TODO: Create LevelManager_Secret
    }
    else if (this->saveManager->nextLevel == 2)
    {
        printf("Ingame_BasicStage_Scene BonusLevel\n");
        // TODO: Create LevelManager_BonusLevel
    }
    else if (this->saveManager->nextLevel == 5)
    {
        printf("Ingame_BasicStage_Scene BossLvl\n");
        // TODO: Create LevelManager_BossLevel
    }
    else
    {
        printf("Ingame_BasicStage_Scene Normal\n");
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
