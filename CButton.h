#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "CTexture.h"
#include <string>

class Button
{
    private:

        TTF_Font *buttonFont;

        SDL_Rect collisionBox;

        int buttonType;

        SDL_Color bgClr; // background color
        SDL_Color fgClr; // foreground color
        SDL_Color borderClr; // border color
        SDL_Color hoverClr; //hover color

        // event variables
        bool leftClicked;  // mouse left clicked button
        bool rightClicked; // mouse right clicked button
        bool mousedOver;   // mouse is hovering over button
        bool mouseClicked;   // is the mouse over the button when clicked
        bool leftReleased;
        bool rightReleased;

        int mAlphaVal;

        Texture mTexture;

    public:

        Button(int x, int y, string name); // button uses an image

        Button(int x, int y, string text, int fontSize); //use default colors
        Button(int x, int y, string text, int fontSize, SDL_Color textColor, SDL_Color fillColor, SDL_Color borderColor, SDL_Color hoverColor);

        ~Button();

        void Draw();         // switch(buttonType)
        void HandleEvents(); // on click, rollover, release,
        void Update();

        void SetAlpha(int newAlpha)
        {
            mAlphaVal = newAlpha;
        }

        bool wasLeftReleased()
        {
            return leftReleased;
        }

        bool wasRightReleased()
        {
            return rightReleased;
        }

        bool wasLeftClicked()
        {
            return leftClicked;
        }

        bool wasRightClicked()
        {
            return rightClicked;
        }

        bool isMousedOver()
        {
            return mousedOver;
        }

        SDL_Rect GetCollisionBox()
        {
            return collisionBox;
        }

        void SetX(int x)
        {
            collisionBox.x = x;
        }

        void SetY(int y)
        {
            collisionBox.y = y;
        }

        void ResetReleases()
        {
            leftReleased = false;
            rightReleased = false;
        }
};
