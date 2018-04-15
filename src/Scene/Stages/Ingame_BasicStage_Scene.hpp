#pragma once

#include "Ingame_Stage_Scene.hpp"
#include "../../Manager/Level/LevelManager_base.hpp"

class Ingame_BasicStage_Scene : public Ingame_Stage_Scene
{
    public:
        LevelManager_base* levelManagerObject;

        Ingame_BasicStage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager);
        ~Ingame_BasicStage_Scene();
};
