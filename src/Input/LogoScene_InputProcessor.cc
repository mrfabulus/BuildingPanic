#include "LogoScene_InputProcessor.hpp"

LogoScene_InputProcessor::LogoScene_InputProcessor()
{
}

LogoScene_InputProcessor::~LogoScene_InputProcessor()
{
}

void LogoScene_InputProcessor::Process()
{
    /*
    bpanic_PullInputFromDI();
    if ( bpanic_IsKeyPressed(DIK_P) )             // "P" "A" "N" "I" "C" code
                                                    // cheat code for unlocking all stages
    {
        v2 = this->inputMask;
        LOBYTE(v2) = v2 | 1;
        this->inputMask = v2;
    }
    if ( bpanic_IsKeyPressed(DIK_A) )
    {
        v3 = this->inputMask;
        LOBYTE(v3) = v3 | 2;
        this->inputMask = v3;
    }
    if ( bpanic_IsKeyPressed(DIK_N) )
    {
        v4 = this->inputMask;
        LOBYTE(v4) = v4 | 4;
        this->inputMask = v4;
    }
    if ( bpanic_IsKeyPressed(DIK_I) )
    {
        v5 = this->inputMask;
        LOBYTE(v5) = v5 | 8;
        this->inputMask = v5;
    }
    result = (void *)bpanic_IsKeyPressed(DIK_C);
    if ( result )
    {
        result = (void *)this->inputMask;
        LOBYTE(result) = (unsigned __int8)result | 0x10;
        this->inputMask = result;
    }
    */
}
