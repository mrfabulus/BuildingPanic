#pragma once

#include "InputProcessorBase.hpp"
#include <cstdint>

class MenuHandler_InputProcessor : public InputProcessorBase
{
    public:
        int16_t word14;
        int32_t dword18;
        int32_t dword1C;
        int32_t dword20;

        MenuHandler_InputProcessor();
        virtual ~MenuHandler_InputProcessor();

        virtual void Process() override;
};
