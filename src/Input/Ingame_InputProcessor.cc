#include "Input/Ingame_InputProcessor.hpp"
#include "Manager/SaveManager.hpp"

/*
DIK_0, DIK_1, DIK_2, DIK_3, DIK_4, DIK_5, DIK_6, DIK_7
DIK_8, DIK_9, DIK_A, DIK_B, DIK_C, DIK_D, DIK_E, DIK_F
DIK_G, DIK_H, DIK_I, DIK_J, DIK_K, DIK_L, DIK_M, DIK_N
DIK_O, DIK_P, DIK_Q, DIK_R, DIK_S, DIK_T, DIK_U, DIK_V
DIK_W, DIK_X, DIK_Y, DIK_Z, DIK_MINUS, DIK_AT, DIK_LBRACKET
DIK_SEMICOLON, DIK_COLON, DIK_RBRACKET, DIK_COMMA, DIK_PERIOD
DIK_SLASH, DIK_BACKSLASH, DIK_UP, DIK_DOWN, DIK_LEFT
DIK_RIGHT
*/

Ingame_InputProcessor::Ingame_InputProcessor(SaveManager* aSaveManager)
    : InputProcessorBase()
{
    // TODO: Create keyindex association array for SDL

    for (int i = 0; i < 8; i++)
        this->player1keyBindingData[i] = aSaveManager->saveState.player1Bindings[i];

    for (int i = 0; i < 8; i++)
        this->player2keyBindingData[i] = aSaveManager->saveState.player2Bindings[i];
}

Ingame_InputProcessor::~Ingame_InputProcessor()
{
}

void Ingame_InputProcessor::Process()
{
    // TODO: Implement 00412DF0
}
