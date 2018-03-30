#include "SDL2_Interface.hpp"
#include "Globals.hpp"
#include "GameManager.hpp"

int main()
{
    if (!gSys.isInitialized())
    {
        cout << "Error initializing SDL2: " << SDL_GetError() << endl;
        return 1;
    }

    if (!gSys.SetupWindow())
        return 1;

    if (!gSys.InitializeRenderer())
        return 1;

    gGameManager = new GameManager();

    // Could not render an empty frame
    if (!gGameManager->lastFrameStatus)
        return 1;

    // Gameloop
    while (true)
    {
        gGameManager->Update();
    }
    
    return 0;
}
