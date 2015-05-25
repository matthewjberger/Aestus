#ifndef CGAME_H
#define CGAME_H

#include "Globals.h"

class GameState;

class Game
{
    public:

        static Game *GetInstance();

        bool Initialize();

        bool LoadContent();

        void UnloadContent();

        void Update();

        void Draw();

        void EventHandler();

        void ChangeState(GameState *state);

        void PushState(GameState *state);

        void PopState();

        void DestroyInstance();

        void ToggleFullScreen();

        SDL_Event GetEvent()
        {
            return event;
        }

        bool IsRunning()
        {
            return running;
        }

        void StopRunning()
        {
            if (debugging == false)
            {
                running = false;
            }
        }

        SDL_Window* GetWindow()
        {
            return window;
        }

        SDL_Surface* GetSurface()
        {
            return screenSurface;
        }

        TTF_Font* GetDefaultFont()
        {
            return font;
        }

        SDL_Color GetDefaultColor()
        {
            return defaultColor;
        }

        SDL_Renderer* GetRenderer()
        {
            return renderer;
        }

        int GetScreenWidth()
        {
            return screenWidth;
        }

        int GetScreenHeight()
        {
            return screenHeight;
        }

        int GetMaxFPS()
        {
            return maxFPS;
        }

        void ClearScreen(int red, int green, int blue);

        int CenterX(int x)
        {
            return (screenWidth - x) / 2;
        }

        int CenterY(int y)
        {
            return (screenHeight - y) / 2;
        }

        string GetDefaultFontName()
        {
            return defaultFontName;
        }

        // GameState stack
        vector<GameState *> GameStates;

    private:

        static Game *inst;

        Game();
        ~Game();

        bool running;

        bool fullscreenEnabled;

        bool debugging;

        char* caption;

        SDL_Window*  window;
        SDL_Surface* screenSurface;

        SDL_Rect gameCamera;

        SDL_Event event;

        SDL_Renderer* renderer;

        SDL_Color defaultColor;

        // Font
        TTF_Font *font;
        string defaultFontName;

        // Screen dimensions
        int screenWidth;
        int screenHeight;

        // Max framerate
        int maxFPS;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameState
{
    public:
        virtual void Init() = 0;
        virtual void Finalize() = 0;

        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual void HandleEvents() = 0;
        virtual void Draw() = 0;
        virtual void Update() = 0;

        void ChangeState(Game *game, GameState *state)
        {
            game->ChangeState(state);
        }

    protected:

        // Get game instance
        Game *game = Game::GetInstance();
};


#endif
