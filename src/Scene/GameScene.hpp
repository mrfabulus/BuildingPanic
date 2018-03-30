#pragma once

#include "../Entity/Entity_base.hpp"
#include "../Entity/EntityLayer.hpp"
#include "../Input/InputProcessorBase.hpp"
#include "../Globals.hpp"

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
        int buffer32[8];
        // char field_870[96];
        uint16_t scenePhaseIndex;
        // __int16 field_8D2;
        InputProcessorBase* inputProcessor;

        GameScene(void* aPaletteDataBytes);

        void PaletteFadeInStart(char, short)
        {

        }

        void PaletteFadeAwayStart(char, short)
        {

        }

        void SetFinishedIfFadesDone()
        {
            if (!this->fadeIn_active && !this->fadeAway_active)
                this->finished = true;
        }

        void AttachEntityToLayer(Entity* aEntity);
        void DetachEntityFromLayer(Entity* aEntity);

        // VTable entries beside sdtor
        virtual int GetNextSceneIDReference();
        virtual void F3();
        virtual void F4();
        virtual void Tick();
};

