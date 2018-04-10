#pragma once

#include "Ingame_Stage_Scene.hpp"

class Ingame_BasicStage_Scene : public Ingame_Stage_Scene
{
    public:
        // HUD_base* levelManagerObject;
        uint32_t* levelManagerObject;

        Ingame_BasicStage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager);
        ~Ingame_BasicStage_Scene();
};
