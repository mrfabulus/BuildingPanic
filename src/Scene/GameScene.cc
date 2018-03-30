#include "GameScene.hpp"
#include "../Globals.hpp"
#include <string.h>

GameScene::GameScene(void* aPaletteDataBytes)
{
    // this->palette1 = 0;
    // this->palette2 = 0;
    this->init_OK = false;
    this->finished = false;
    this->phantomTicksEnabled = false;
    this->ticksLeftUntilReEval = 0;
    this->paletteDataPtr = aPaletteDataBytes;
    this->fadeFrameProgressCount = 0;
    this->word846 = 0;
    this->fadeAway_active = false;
    this->fadeIn_active = false;
    this->tick_part1_optional_do_number = 0;
    this->word84C_tick1_related = 0;
    this->tick_part4_optional_do_fade_related = 0;
    this->scenePhaseIndex = 0;
    this->inputProcessor = nullptr;

    // Create layers
    for (int i = 0; i < 5; i++)
    {
        layers[i] = new EntityLayer();
        layers[i]->latestEntity = nullptr;
        layers[i]->nextAttachedEntity = nullptr;
        layerEntityCounts[i] = 0;
    }

    memset(this->buffer32, 0, sizeof(this->buffer32));
    
    // if (gNonStandardDimensions)
    if (true)
    {
        this->dwStartingEntry = 0;
        this->dwCount = 256;
    }
    else
    {
        this->dwStartingEntry = 10;
        this->dwCount = 236;
    }

    // TODO: Init palettes
    if ( // bpanic_InitDDPaletteFromData(&this->palette1, aPaletteDataBytes)
        // && bpanic_InitDDPaletteFromData(&this->palette2, aPaletteDataBytes)
        /* && bpanic_SetMainDDSurfacePalette(&this->palette1) */ true)
    {
        this->init_OK = 1;
    }
}

int GameScene::GetNextSceneIDReference()
{
}

void GameScene::F3()
{
}

void GameScene::F4()
{
}

void GameScene::Tick()
{
}
