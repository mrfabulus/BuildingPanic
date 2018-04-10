#include "Ingame_Stage1_Scene.hpp"

Ingame_Stage1_Scene::Ingame_Stage1_Scene(SaveManager* aSaveManager)
    : Ingame_BasicStage_Scene(nullptr, aSaveManager)
{
    this->LoadTileSets();
    this->AttachEntities();
}

Ingame_Stage1_Scene::~Ingame_Stage1_Scene()
{
}

void Ingame_Stage1_Scene::LoadTileSets()
{
}
