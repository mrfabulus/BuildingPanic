#include "Ingame_BasicStage_Scene.hpp"

Ingame_BasicStage_Scene::Ingame_BasicStage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager)
    : Ingame_Stage_Scene(aPaletteDataBytes, aSaveManager)
{

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
