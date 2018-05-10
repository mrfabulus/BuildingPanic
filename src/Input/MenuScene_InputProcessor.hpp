#pragma once

#include <cstdint>
#include "Input/InputProcessorBase.hpp"

class MenuScene_InputProcessor : public InputProcessorBase
{
    public:
        MenuScene_InputProcessor();
        virtual ~MenuScene_InputProcessor();

        int16_t word14;

        virtual void Process() override;
};