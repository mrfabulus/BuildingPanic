#pragma once

#include "../Globals.hpp"

class LayerEntity;
class Entity_base;
class Entity;
class InputProcessorBase;

class GameScene
{
    public: 
        // LPDIRECTDRAWPALETTE palette1;
        // LPDIRECTDRAWPALETTE palette2;
        SDL_Palette* palette1;
        SDL_Palette* palette2;
        bool init_OK;
        bool finished;
        bool phantomTicksEnabled;
        int32_t ticksLeftUntilReEval;
        LayerEntity* layers[5];
        int16_t layerEntityCounts[5];
        // __int16 word3A;
        void* paletteDataPtr;
        // PALETTEENTRY paletteEntries[512];
        uint16_t dwStartingEntry;
        uint16_t dwCount;
        uint16_t fadeFrameProgressCount;
        int16_t word846;
        bool fadeAway_active;
        bool fadeIn_active;
        int8_t tick_part1_optional_do_number;
        int16_t word84C_tick1_related;
        int16_t tick_part4_optional_do_fade_related;
        int32_t buffer32[8];
        // char field_870[96];
        uint16_t scenePhaseIndex;
        // __int16 field_8D2;
        InputProcessorBase* inputProcessor;

        GameScene(void* aPaletteDataBytes);

        void PaletteFadeInStart(char, short);

        void PaletteFadeAwayStart(char, short);

        void SetFinishedIfFadesDone();

        void AttachEntityToLayer(Entity* aEntity);
        void DetachEntityFromLayer(Entity* aEntity);

        void Tick(); // generic tick/update (shared between scenes)
        void RenderLayers();
        void UpdateEntities();

        // VTable entries beside sdtor
        virtual int GetNextSceneIDReference();
        virtual void F3();
        virtual void UpdateLayer(LayerEntity* aLayer, int16_t aLayerEntityCount);
        virtual void Update(); // scene specific virtual function
};

