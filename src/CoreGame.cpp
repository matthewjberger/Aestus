#include "CoreGame.h"
#include "PresentationState.h"

Game::Game()
{
    // Initialize game variables
    running = true;
    fullscreenEnabled = false;

    debugging = false;

    // Set default resolution
    screenWidth  = 240;
    screenHeight = 728;

    gameCamera.x = 0;
    gameCamera.y = 0;
    gameCamera.w = screenWidth;
    gameCamera.h = screenHeight;

    font = NULL;

    char* caption = "";

    window = NULL;
    screenSurface = NULL;

    renderer = NULL;

    // Set default color to white
    defaultColor = { 101, 156, 239 };

    // Set Max FPS
    maxFPS = 60;

    // Seed RNG
    srand((unsigned int)time(NULL));
}

Game::~Game()
{
}

Game *Game::inst = 0;

Game *Game::GetInstance()
{
    if (inst == 0)
    {
        inst = new Game();
    }

    return inst;
}

bool Game::Initialize()
{
    // Set caption
    caption = "Aestus";

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized!\n SDL_Error: %s\n", SDL_GetError() );

        return false;
    }
    else
    {
        // Create the window
        if (fullscreenEnabled == true)
        {
            window = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NULL, NULL, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        else if (fullscreenEnabled == false)
        {
            window = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        }

        if (window == NULL)
        {
            printf("Window could not be created!\n SDL_Error: %s\n", SDL_GetError());

            StopRunning();

            return false;
        }
        else
        {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL_Error: %s", SDL_GetError());

                StopRunning();
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize scaling
                SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); // smooth scaling
                SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);


                // Initialize extension libraries

                    // Initialize PNG loading
                    int imgFlags = IMG_INIT_PNG;

                    if (!(IMG_Init(imgFlags) & imgFlags))
                    {
                        printf("SDL_Image could not initialize!\n SDL_image Error: %s\n", IMG_GetError());

                        StopRunning();
                    }

                    // Initialize SDL_ttf
                    if (TTF_Init() == -1)
                    {
                        printf("SDL_ttf could not initialize!\n SDL_ttf Error: %s\n", TTF_GetError());

                        StopRunning();
                    }

                    // Initialize SDL_mixer
                    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
                    {
                        printf("SDL_mixer could not initialize!\n SDL_ttf Error: %s\n", Mix_GetError());

                        StopRunning();
                    }

                // Initialize screen surface
                screenSurface = SDL_GetWindowSurface(window);
            }

        }
    }

    return true;
}

bool Game::LoadContent()
{
    // Load font
    font = TTF_OpenFont("Fonts/FreeSans.ttf", 36);

    if (font == NULL)
    {
        printf("Unable to open font!\n SDL_ttf Error: %s\n", TTF_GetError());

        StopRunning();

        return false;
    }


    //-- Load game content here

    ChangeState(PresentationState::GetInstance());

    //--

    return true;
}

void Game::UnloadContent()
{

    // Release game content, Free Surfaces, Close Libraries
    if (!GameStates.empty())
    {
        GameStates.back()->Finalize();
        GameStates.pop_back();
    }

    /************************************************/

    // Free font
    TTF_CloseFont(font);
    font = NULL;

    // Destroy Window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    renderer = NULL;
    window   = NULL;

    // Quit subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Game::ChangeState(GameState *state)
{
    if (!GameStates.empty()) // if there is a state, clean it up and pop it off
    {
        GameStates.back()->Finalize();
        GameStates.pop_back();
    }

    GameStates.push_back(state); // push on the new one and initialize it
    GameStates.back()->Init();
}

void Game::PushState(GameState *state)
{
    if (!GameStates.empty())  // pause state if there is one already on stack
    {
        GameStates.back()->Pause();
    }

    GameStates.push_back(state); // push state onto stack and initialize it
    GameStates.back()->Init();
}

void Game::PopState()
{
    if (!GameStates.empty())//if somethings on the stack and finish up state then pop it off
    {
        GameStates.back()->Finalize();
        GameStates.pop_back();
    }

    if (!GameStates.empty()) // if there's a state left, it is paused, so resume it
    {
        GameStates.back()->Resume();
    }
}

void Game::Update()
{
    // Place Update logic here
    GameStates.back()->Update();

}

void Game::Draw()
{
    // Place Rendering logic here
    GameStates.back()->Draw();

}

void Game::EventHandler()
{
    while( SDL_PollEvent(&event) != 0 )
    {
        //Place Event Handling Functions here
        GameStates.back()->HandleEvents();

        if (event.type == SDL_QUIT)
        {
            StopRunning();
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_F11:
                this->ToggleFullScreen();
                break;

            case SDLK_ESCAPE:
                StopRunning();
                break;
            }
        }
    }
}

void Game::DestroyInstance()
{
    delete inst;

    inst = 0;
}

void Game::ToggleFullScreen()
{
    if (fullscreenEnabled == false)
    {
        // Maximize
        SDL_SetWindowFullscreen(window, SDL_TRUE);

        // Set status
        fullscreenEnabled = true;
    }
    else if (fullscreenEnabled == true)
    {
        // Minimize
        SDL_SetWindowFullscreen(window, SDL_FALSE);

        // Set status
        fullscreenEnabled = false;

    }
}

void Game::ClearScreen(int red, int green, int blue)
{
    // Set Clear color
    SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);

    // Clear screen with renderer
    SDL_RenderClear(renderer);
}
