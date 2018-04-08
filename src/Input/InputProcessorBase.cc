#include "InputProcessorBase.hpp"

InputProcessorBase::InputProcessorBase()
{
}

InputProcessorBase::~InputProcessorBase()
{
}

void InputProcessorBase::Tick()
{
    this->savedInputMask = this->inputMask;
    this->inputMask = 0;
    this->Process();
    uint32_t postTickMask = this->inputMask;
    this->newButtonPressesMask  =  postTickMask & (postTickMask ^ this->savedInputMask);
    this->newButtonReleasesMask = ~postTickMask & (postTickMask ^ this->savedInputMask);
}

void InputProcessorBase::Process()
{
}
