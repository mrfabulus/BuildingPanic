#include "Ingame_Stage_Scene.hpp"

Ingame_Stage_Scene::Ingame_Stage_Scene(SDL_Color* aPaletteDataBytes, SaveManager* aSaveManager)
    : GameScene(aPaletteDataBytes)
{
    this->saveManager = aSaveManager;
    this->dword90C = 0;
    this->dword910 = 0;
    this->sceneSoundManager = nullptr;
    
    /*
    cPtr = (int)&this->hudPMark1;
    i = 2;

    do
    {
        *(_DWORD *)(cPtr + 64) = 0;                 // zero init 4 offseted buffers 2 times
                                                    // dword918, dword91C
        *(_DWORD *)cPtr = 0;                        // dword8D8, dword8DC
        *(_DWORD *)(cPtr + 0x19C) = 0;              // dwordA74, dwordA78
        *(_DWORD *)(cPtr + 0x1A4) = 0;              // dwordA7C, dwordA80
        cPtr += 4;
        --i;
    }
    while ( i );
    */

    memset(this->wallEntities, 0, sizeof(this->wallEntities));
    memset(this->hundredScoreEntities, 0, sizeof(this->hundredScoreEntities));
    memset(this->itemEntities, 0, sizeof(this->itemEntities));
    this->hudTextEntity = nullptr;
    this->dwordA88 = 0;
    this->gridImageEntity = nullptr;
    this->stageBackgroundTileSetEntity = nullptr;
    memset(this->wallBarEntities, 0, sizeof(this->wallBarEntities));
    memset(this->lampEntities, 0, sizeof(this->lampEntities));
    this->pauseTextEntity = nullptr;
    this->dword908 = 0;

    
}

Ingame_Stage_Scene::~Ingame_Stage_Scene()
{
}

void Ingame_Stage_Scene::CreateEntities()
{
}

void Ingame_Stage_Scene::AttachEntities()
{
}
