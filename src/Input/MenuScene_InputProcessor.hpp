#pragma once

#include <cstdint>
#include "Input/InputProcessorBase.hpp"

class MenuScene_InputProcessor : public InputProcessorBase
{
    public:
        MenuScene_InputProcessor();
        virtual ~MenuScene_InputProcessor();

        uint16_t lastButtonPressed;

        virtual void Process() override;
};