#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
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

        bool beingDragged;

        int mAlphaVal;

        Texture mTexture;
        Texture mAltTexture;

        bool usingAltTexture;
        bool showCollisionBox;
        bool useCollisionBox;

        SDL_Rect visRect;

    public:

        Button(int x, int y, string name); // button uses an image
        Button(string stdImagePath, string altImagePath, int x=0, int y=0); // button uses an image and an alternate image

        Button(int x, int y, string text, int fontSize); //use default colors
        Button(int x, int y, string text, int fontSize, SDL_Color textColor, SDL_Color fillColor, SDL_Color borderColor, SDL_Color hoverColor);

        ~Button();

        void Draw();         // switch(buttonType)
        void HandleEvents(); // on click, rollover, release,
        void Update();

        void Free();

        void ShowAltImage(bool show) { usingAltTexture = show; }
        void ToggleAltImage();
        bool UsingAltImage() { return usingAltTexture; }

        void SetAlpha(int newAlpha)
        {
            mAlphaVal = newAlpha;
        }

        bool WasLeftReleased()
        {
            return leftReleased;
        }

        bool WasRightReleased()
        {
            return rightReleased;
        }

        bool WasLeftClicked()
        {
            return leftClicked;
        }

        bool WasRightClicked()
        {
            return rightClicked;
        }

        bool IsMousedOver()
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
            leftReleased  = false;
            rightReleased = false;
            leftClicked   = false;
            rightClicked  = false;
        }

        void ShowCollisionBox(bool vis)
        {
            showCollisionBox = vis;
        }

        void UseCollisionBox(bool use)
        {
            useCollisionBox = use;
        }

        bool IsBeingDragged()
        {
            return beingDragged;
        }

};
