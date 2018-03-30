#pragma once

#include "../Entity/Entity_base.hpp"
#include "../Entity/EntityLayer.hpp"
#include "../Input/InputProcessorBase.hpp"

class GameScene
{
    public: 
        // LPDIRECTDRAWPALETTE palette1;
        // LPDIRECTDRAWPALETTE palette2;
        bool init_OK;
        bool finished;
        bool phantomTicksEnabled;
        int ticksLeftUntilReEval;
        EntityLayer* layers[5];
        short layerEntityCounts[5];
        // __int16 word3A;
        void* paletteDataPtr;
        // PALETTEENTRY paletteEntries[512];
        uint16_t dwStartingEntry;
        uint16_t dwCount;
        uint16_t fadeFrameProgressCount;
        short word846;
        bool fadeAway_active;
        bool fadeIn_active;
        char tick_part1_optional_do_number;
        short word84C_tick1_related;
        short tick_part4_optional_do_fade_related;
        // int buffer32[8];
        // char field_870[96];
        uint16_t scenePhaseIndex;
        // __int16 field_8D2;
        InputProcessorBase* inputProcessor;

        GameScene(void* aPaletteDataBytes)
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

            // TODO: Init palettes
        }

        void PaletteFadeInStart(char, short)
        {

        }
};

