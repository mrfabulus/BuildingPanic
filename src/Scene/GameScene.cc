#include "GameScene.hpp"
#include "../Globals.hpp"
#include "../Entity/Generic/Entity_base.hpp"
#include "../Entity/Generic/LayerEntity.hpp"
#include "../Entity/Generic/Entity.hpp"
#include "../Input/InputProcessorBase.hpp"
#include <string.h>
#include <iostream>

GameScene::GameScene(SDL_Color* aPaletteDataBytes)
{
    this->palette1 = nullptr;
    this->palette2 = nullptr;
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
        layers[i] = new LayerEntity();
        layers[i]->latestEntity = nullptr;
        layers[i]->nextAttachedEntity = nullptr;
        layerEntityCounts[i] = 0;
    }

    memset(this->buffer32, 0, sizeof(this->buffer32));
    
    if (gNonStandardDimensions)
    {
        this->dwStartingEntry = 0;
        this->dwCount = 256;
    }
    else
    {
        this->dwStartingEntry = 10;
        this->dwCount = 236;
    }

    if (   this->InitPaletteFromColors(&this->palette1, aPaletteDataBytes)
        && this->InitPaletteFromColors(&this->palette2, aPaletteDataBytes)
        && this->InitMainSurfacePalette(this->palette1))
    {
        std::cout << "GameScene init OK" << std::endl;
        this->init_OK = true;
    }
    else
    {
        std::cout << "GameScene init failed" << std::endl;
    }
}

GameScene::~GameScene()
{
    // TODO: Potentially release palettes?

    for (int i = 0; i < 5; i++)
        delete this->layers[i];
}

void GameScene::AttachEntityToLayer(Entity* aEntity)
{
    // push_front() type of logic into the linked list
    Entity* cFirstEntity = this->layers[aEntity->layerIndex]->nextAttachedEntity;

    if (cFirstEntity)
    {
        // set the current first element to be the next-> of this entity
        aEntity->nextAttachedEntity = cFirstEntity;
        cFirstEntity->latestEntity = aEntity;
    }
    else
    {
        // ->next is zero in case there were no entities attached to this layer
        aEntity->nextAttachedEntity = nullptr;
    }

    // latestEntity is set to the EntityLayer the entity resides on
    aEntity->latestEntity = (Entity*) this->layers[aEntity->layerIndex]; // note: pointer conversion was explicitly added later

    // set this entity to be the first element of the linked list
    this->layers[aEntity->layerIndex]->nextAttachedEntity = aEntity;
    // end of push_front() logic

    // increase entity count on layer
    this->layerEntityCounts[aEntity->layerIndex]++;
}

// I do not understand this function but looks good! lmao
void GameScene::DetachEntityFromLayer(Entity* aEntity)
{
    LayerEntity* cLayer = this->layers[aEntity->layerIndex];

    // Check if this entity is the first in the linked list
    if (cLayer->nextAttachedEntity == aEntity)
    {
        // Set the next entity to be the first in the linked list
        Entity* nextEntity = aEntity->nextAttachedEntity;
        cLayer->nextAttachedEntity = nextEntity;

        if (nextEntity != nullptr)
        {
            // ???
            this->layers[aEntity->layerIndex]->nextAttachedEntity->latestEntity = (Entity*) this->layers[aEntity->layerIndex];
            // note: pointer conversion was explicitly added later                ^
        }
    }
    else
    {
        // entity is not first in linked list
        aEntity->latestEntity->nextAttachedEntity = aEntity->nextAttachedEntity;

        Entity* nextEntity = aEntity->nextAttachedEntity;

        if (nextEntity != nullptr)
        {
            // ???
            nextEntity->latestEntity = aEntity->latestEntity;
        }
    }

    // Decrease entity count on layer
    this->layerEntityCounts[aEntity->layerIndex]--;
}

// VTABLE
int GameScene::GetNextSceneIDReference()
{
}

void GameScene::MakeSureImagesAreReady()
{
}

void GameScene::UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount)
{
    // Contains code but I couldn't reverse it for the time being
    // ???
}

void GameScene::Update()
{
}
// END OF VTABLE

void GameScene::Tick()
{
    std::cout << "GameScene::Tick" << std::endl;
    this->Update();

    if (this->phantomTicksEnabled)
    {    
        this->RenderLayers();
        return;
    }

    this->UpdateEntities();

    if (!this->finished)
    {
        if (this->tick_part1_optional_do_number)
        {
            // TODO: implement
        }

        // First, rotate palette if applicable
        if (this->fadeIn_active)
        {
            // TODO: Implement
            // GameScene_paletteRotation_fadeIn()
        }
        else if (this->fadeAway_active)
        {
            // TODO: Implement
            // GameScene_paletteRotation_fadeAway()
        }

        // Simplified original logic a bit, not sure if its correct
        if (!this->fadeIn_active && !this->fadeAway_active && this->tick_part4_optional_do_fade_related)
        {
            // TODO: Implement
            // GameScene_402A90_paletteRotation()
        }

        this->RenderLayers();
        --this->ticksLeftUntilReEval;
    }
}

void GameScene::RenderLayers()
{
    for (int i = 0; i < 5; i++)
    {
        Entity* currentEntity = this->layers[i]->nextAttachedEntity;

        while (currentEntity != nullptr)
        {
            currentEntity->Render();
            currentEntity = currentEntity->nextAttachedEntity;
        }
    }
}

void GameScene::PaletteFadeInStart(char, short)
{

}

void GameScene::PaletteFadeAwayStart(char, short)
{

}

void GameScene::SetFinishedIfFadesDone()
{
    if (!this->fadeIn_active && !this->fadeAway_active)
        this->finished = true;
}

void GameScene::UpdateEntities()
{
    for (int i = 0; i < 5; i++)
    {
        Entity* currentEntity = this->layers[i]->nextAttachedEntity;

        if (currentEntity != nullptr)
        {
            // Call once for each layer
            this->UpdateLayer(this->layers[i], this->layerEntityCounts[i]);

            while (currentEntity != nullptr)
            {
                // Call once for each entity
                currentEntity->Update();
                currentEntity = currentEntity->nextAttachedEntity;
            }
        }
    }
}

bool GameScene::InitPaletteFromColors(SDL_Palette** aOutPalette, SDL_Color* aColors)
{
    // TODO: Error handling
    SDL_Palette* newPalette = SDL_AllocPalette(256);
    SDL_PixelFormat format;
    format.format = SDL_PIXELFORMAT_INDEX8;
    format.palette = newPalette;
    format.BitsPerPixel = 8;
    // format.By

    SDL_SetPixelFormatPalette(&format, newPalette);

    SDL_SetPaletteColors(newPalette, aColors, 0, 256);
    *aOutPalette = newPalette;

    return true;
}

bool GameScene::InitMainSurfacePalette(SDL_Palette* aPalette)
{
    int result = SDL_SetSurfacePalette(gSys.GetMainSurface(), aPalette);
    std::cout << "SDL_SetSurfacePalette returned " << result << std::endl;

    if (result < 0)
    {
        std::cout << SDL_GetError() << std::endl;
    }

    return true;
}
