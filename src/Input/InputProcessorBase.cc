#include "InputProcessorBase.hpp"
#include <iostream>

InputProcessorBase::InputProcessorBase()
{
}

InputProcessorBase::~InputProcessorBase()
{
}

void InputProcessorBase::Tick()
{
    // std::cout << "InputProcessorBase tick" << std::endl;
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
