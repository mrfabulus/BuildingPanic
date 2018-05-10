#pragma once

#include "Input/InputProcessorBase.hpp"

class LogoScene_InputProcessor : public InputProcessorBase
{
    public:
        LogoScene_InputProcessor();
        virtual ~LogoScene_InputProcessor();

        virtual void Process() override;
};
