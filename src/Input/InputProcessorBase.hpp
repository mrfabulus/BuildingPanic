#pragma once

class InputProcessorBase
{
    int32_t inputMask;
    int32_t savedInputMask;
    int32_t postInputTickMask1;
    int32_t postInputTickMask2;

    virtual void Process();
};
