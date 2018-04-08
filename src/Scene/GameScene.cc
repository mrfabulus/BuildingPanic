#include "GameScene.hpp"
#include "../Globals.hpp"
#include "../Entity/Generic/GameObject.hpp"
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
        layers[i]->previousAttachedEntity = nullptr;
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
    if (this->palette2 != nullptr)
    {
        SDL_FreePalette(this->palette2);
        this->palette2 = nullptr;
    }

    if (this->palette1 != nullptr)
    {
        SDL_FreePalette(this->palette1);
        this->palette1 = nullptr;
    }

    for (int i = 0; i < 5; i++)
        delete this->layers[i];
}

void GameScene::AttachGameObjectToLayer(GameObject* aEntity)
{
    // push_front() type of logic into the linked list
    GameObject* cFirstEntity = this->layers[aEntity->layerIndex]->nextAttachedEntity;

    if (cFirstEntity)
    {
        // set the current first element to be the next-> of this entity
        aEntity->nextAttachedEntity = cFirstEntity;
        cFirstEntity->previousAttachedEntity = aEntity;
    }
    else
    {
        // ->next is zero in case there were no entities attached to this layer
        aEntity->nextAttachedEntity = nullptr;
    }

    // previousAttachedEntity is set to the EntityLayer the entity resides on
    aEntity->previousAttachedEntity = this->layers[aEntity->layerIndex];

    // set this entity to be the first element of the linked list
    this->layers[aEntity->layerIndex]->nextAttachedEntity = aEntity;
    // end of push_front() logic

    // increase entity count on layer
    this->layerEntityCounts[aEntity->layerIndex]++;
}

void GameScene::DetachGameObjectFromLayer(GameObject* aEntity)
{
    LayerEntity* cLayer = this->layers[aEntity->layerIndex];

    // Check if this entity is the first in the linked list
    if (cLayer->nextAttachedEntity == aEntity)
    {
        // entity is first in linked list
        // Set the next entity to be the first in the linked list
        GameObject* nextEntity = aEntity->nextAttachedEntity;
        cLayer->nextAttachedEntity = nextEntity;

        // if the new first entity exists, set its prev-> to the layer entity
        if (nextEntity != nullptr)
        {
            this->layers[aEntity->layerIndex]->nextAttachedEntity->previousAttachedEntity = this->layers[aEntity->layerIndex];
        }
    }
    else
    {
        // entity is not first in linked list
        // set prev entitys next-> to the entity next to this one
        aEntity->previousAttachedEntity->nextAttachedEntity = aEntity->nextAttachedEntity;

        GameObject* nextEntity = aEntity->nextAttachedEntity;

        // if there is a next entity, set its prev-> to the entity before this one
        if (nextEntity != nullptr)
        {
            nextEntity->previousAttachedEntity = aEntity->previousAttachedEntity;
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
    // std::cout << "GameScene::Tick" << std::endl;
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
        GameObject* currentEntity = this->layers[i]->nextAttachedEntity;

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
        GameObject* currentEntity = this->layers[i]->nextAttachedEntity;

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

    // TODO: Solve "SDL_SetPixelFormatPalette() passed a palette that doesn't match the format"
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
