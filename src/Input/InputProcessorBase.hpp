#pragma once

#include <cstdint>

class InputProcessorBase
{
    public:
        uint32_t inputMask;
        uint32_t savedInputMask;
        uint32_t newButtonPressesMask;
        uint32_t newButtonReleasesMask;

        InputProcessorBase();
        virtual ~InputProcessorBase();

        void Tick();
        virtual void Process();
};
