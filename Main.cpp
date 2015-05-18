/*
  ||||||||||||||||||||||||||||
  || C++/SDL_2 Game Engine  ||
  || Created by Matt Berger ||
  ||||||||||||||||||||||||||||
*/

#include "CoreGame.h"

int main(int argc, char *args[])
{
    // Create Game and debug instances
    Game *game = Game::GetInstance();    

    bool fullscreen = false;

    if (game->Initialize() == false)
    {
        printf("Failed to Initialize!");

        game->StopRunning();

        return 1;
    }

    if (game->LoadContent() == false)
    {
        printf("Failed to load content");

        game->StopRunning();

        return 1;
    }

    while (game->IsRunning())
    {

        // Run game
        game->EventHandler();
        game->Update();
        game->Draw();

        // Update window
        SDL_RenderPresent( game->GetRenderer() );

        // Control framerate
        SDL_Delay(1000 / game->GetMaxFPS());

    }

    game->UnloadContent();

    game->DestroyInstance();

    return 0;
}