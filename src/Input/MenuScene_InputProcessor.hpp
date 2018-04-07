#pragma once

#include "InputProcessorBase.hpp"

class MenuScene_InputProcessor : public InputProcessorBase
{
    public:
        MenuScene_InputProcessor();
        virtual ~MenuScene_InputProcessor();

        virtual void Process() override;
};