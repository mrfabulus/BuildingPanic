#include "SDL2_Interface.hpp"
#include "Globals.hpp"
#include "Manager/GameManager.hpp"

int main()
{
    if (!gSys.IsVideoInitialized())
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
    while (gGameloopRunning)
    {
        gSys.ProcessEvents();

        if (gGameloopActive)
        {
            gGameManager->Update();
        }
        else
        {
            // Wait 100 ms every time in case the gameloop is inactive to avoid busy waiting
            SDL_Delay(100);
        }
    }
    
    return 0;
}
