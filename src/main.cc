#include "SDL2_Interface.hpp"
#include "Globals.hpp"
#include "Manager/GameManager.hpp"

int main()
{
    if (!gSys.isVideoInitialized())
    {
        cout << "Error initializing SDL2 video: " << SDL_GetError() << endl;
        return 1;
    }

    if (!gSys.SetupWindow())
        return 1;

    if (!gSys.Initialize())
        return 1;

    gGameManager = new GameManager();

    // Gameloop
    while (gGameloopActive)
    {
        gGameManager->Update();
    }
    
    return 0;
}
