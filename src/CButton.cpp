#include "Globals.h"
#include "CoreGame.h"

Button::Button(int x, int y, string name)
{
    buttonType = IMAGE;

    buttonFont = NULL;

    leftReleased     = false;
    rightReleased    = false;
    leftClicked      = false;
    rightClicked     = false;
    mousedOver       = false;
    beingDragged     = false;
    showCollisionBox = false;
    useCollisionBox  = false;
    hoverEnabled     = true;

    hoverClr.r      = 0;
    hoverClr.g      = 180;
    hoverClr.b      = 0;

    mTexture.LoadImage(name.c_str());

    collisionBox.x  = x;
    collisionBox.y  = y;
    collisionBox.w  = mTexture.GetWidth();
    collisionBox.h  = mTexture.GetHeight();

    mAlphaVal       = 255;

    // Enable blending
    mTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

Button::Button(int x, int y, string text, int fontSize)
{
    Game *game = Game::GetInstance();

    string fontPath = "Fonts/" + game->GetDefaultFontName();
    buttonFont = TTF_OpenFont(fontPath.c_str(), fontSize);

    fgClr.r = 255;
    fgClr.g = 255;
    fgClr.b = 255; // white text

    bgClr.r = 0;
    bgClr.g = 0;
    bgClr.b = 255; // blue bg

    borderClr.r = 255;
    borderClr.g = 0;
    borderClr.b = 0; // red border

    hoverClr.r = 0;
    hoverClr.g = 180;
    hoverClr.b = 0;

    mTexture.LoadText(text, fgClr, buttonFont);

    collisionBox.x = x;
    collisionBox.y = y;
    collisionBox.w = mTexture.GetWidth();
    collisionBox.h = mTexture.GetHeight();

    buttonType = TEXT;

    leftReleased     = false;
    rightReleased    = false;
    leftClicked      = false;
    rightClicked     = false;
    mousedOver       = false;
    beingDragged     = false;
    showCollisionBox = false;
    useCollisionBox  = false;
    hoverEnabled     = true;

    mAlphaVal = 255;

    // Enable blending
    mTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

Button::Button(int x, int y, string text, int fontSize, SDL_Color textColor, SDL_Color fillColor, SDL_Color borderColor, SDL_Color hoverColor)
{
    Game* game = game->GetInstance();

    buttonFont = game->GetDefaultFont();

    fgClr     = textColor;
    bgClr     = fillColor;
    borderClr = borderColor;
    hoverClr  = hoverColor;

    mTexture.LoadText(text, fgClr, buttonFont);

    collisionBox.x = x;
    collisionBox.y = y;
    collisionBox.w = mTexture.GetWidth();
    collisionBox.h = mTexture.GetHeight();

    buttonType = TEXT;

    leftReleased     = false;
    rightReleased    = false;
    leftClicked      = false;
    rightClicked     = false;
    mousedOver       = false;
    beingDragged     = false;
    showCollisionBox = false;
    hoverEnabled     = true;

    mAlphaVal = 255;

    // Enable blending
    mTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

Button::Button(string stdImagePath, string altImagePath, int x, int y)
{
    buttonType     = ALTIMG;

    buttonFont = NULL;

    leftReleased     = false;
    rightReleased    = false;
    leftClicked      = false;
    rightClicked     = false;
    mousedOver       = false;
    beingDragged     = false;
    showCollisionBox = false;
    useCollisionBox  = false;
    hoverEnabled     = false;

    hoverClr.r      = 255;
    hoverClr.g      = 255;
    hoverClr.b      = 255;

    usingAltTexture = false;

    mTexture.LoadImage(stdImagePath.c_str());
    mAltTexture.LoadImage(altImagePath.c_str());

    collisionBox.x = x;
    collisionBox.y = y;
    collisionBox.w = mTexture.GetWidth();
    collisionBox.h = mTexture.GetHeight();

    mAlphaVal      = 255;

    // Enable blending
    mTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
    mAltTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

Button::~Button()
{
    Free();
}

void Button::Free()
{
    mTexture.Free();
    mAltTexture.Free();
    if(buttonFont != NULL) TTF_CloseFont(buttonFont);

}

void Button::Draw()
{
    // Get game instance
    Game *game = Game::GetInstance();

    // Set alpha
    mTexture.SetAlpha(mAlphaVal);

    if (buttonType == IMAGE)
    {
        if (!mousedOver)
        {
            // draw image
            mTexture.SetColor(255, 255, 255);
            mTexture.Draw(collisionBox.x, collisionBox.y);
        }
        else if (mousedOver)
        {
            // draw image with hover color modulation
            if(hoverEnabled) mTexture.SetColor(hoverClr.r, hoverClr.g, hoverClr.b);
            mTexture.Draw(collisionBox.x,  collisionBox.y);
        }
    }
    else if(buttonType == ALTIMG)
    {
        if (!mousedOver)
        {
            // draw correct image
            if(!usingAltTexture)
            {
                mTexture.SetColor(255, 255, 255);
                mTexture.Draw(collisionBox.x, collisionBox.y);
            }
            else
            {
                mAltTexture.SetColor(255, 255, 255);
                mAltTexture.Draw(collisionBox.x - abs(collisionBox.w/2 - mAltTexture.GetWidth()/2), collisionBox.y - abs(collisionBox.h/2 - mAltTexture.GetHeight()/2));
            }
        }
        else if (mousedOver)
        {
            // draw correct image
            if(!usingAltTexture)
            {
                // draw image with hover color modulation
                if(hoverEnabled) mTexture.SetColor(hoverClr.r, hoverClr.g, hoverClr.b);
                mTexture.Draw(collisionBox.x, collisionBox.y);
            }
            else
            {
                // draw image with hover color modulation
                if(hoverEnabled) mAltTexture.SetColor(hoverClr.r, hoverClr.g, hoverClr.b);
                mAltTexture.Draw(collisionBox.x - abs(collisionBox.w/2 - mAltTexture.GetWidth()/2), collisionBox.y - abs(collisionBox.h/2 - mAltTexture.GetHeight()/2));
            }
        }

        if(showCollisionBox)
        {
            SDL_SetRenderDrawColor( game->GetRenderer(), 0, 255, 0, 255);
            SDL_RenderDrawRect(game->GetRenderer(), &collisionBox);
        }
    }
    else if (buttonType == TEXT)
    {
        if (!mousedOver)
        {
            // draw bg box
            SDL_SetRenderDrawColor(game->GetRenderer(), bgClr.r, bgClr.g, bgClr.b, 255);
            SDL_RenderFillRect(game->GetRenderer(), &collisionBox);

            // draw border outline
            SDL_SetRenderDrawColor(game->GetRenderer(), borderClr.r, borderClr.g, borderClr.b, 255);
            SDL_RenderDrawRect(game->GetRenderer(), &collisionBox);

            // draw text
            mTexture.SetColor(fgClr.r, fgClr.g, fgClr.b);
            mTexture.Draw(collisionBox.x, collisionBox.y);

        }
        else if (mousedOver)
        {
            // draw bg box
            if(hoverEnabled)
                SDL_SetRenderDrawColor(game->GetRenderer(), hoverClr.r, hoverClr.g, hoverClr.b, 255);
            else
                SDL_SetRenderDrawColor(game->GetRenderer(), bgClr.r, bgClr.g, bgClr.b, 255);

            SDL_RenderFillRect(game->GetRenderer(), &collisionBox);

            // draw border outline
            SDL_SetRenderDrawColor(game->GetRenderer(), borderClr.r, borderClr.g, borderClr.b, 255);
            SDL_RenderDrawRect(game->GetRenderer(), &collisionBox);

            // draw text
            mTexture.SetColor(fgClr.r, fgClr.g, fgClr.b);
            mTexture.Draw(collisionBox.x, collisionBox.y);
        }
    }
}

void Button::HandleEvents()
{
    // Get game instance
    Game *game = Game::GetInstance();

    SDL_Event event = game->GetEvent();

    ResetReleases();

    // Mouse position variables
    int x;
    int y;

    SDL_GetMouseState(&x, &y);

    if (event.type == SDL_MOUSEMOTION)
    {
        x = event.motion.x;
        y = event.motion.y;

        if (MARCollisionTest(x, y, collisionBox))
        {
            mousedOver = true;
        }
        else
        {
            mousedOver = false;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        switch (event.button.button)
        {
            case SDL_BUTTON_LEFT:

                if (mousedOver)
                {
                    beingDragged = true;
                    leftClicked  = true;    // if the mouse clicks and is over the button, register it
                }

                break;

            case SDL_BUTTON_RIGHT:

                if (mousedOver)
                {
                    rightClicked = true;
                }

                break;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP)
    {
        switch (event.button.button)
        {
            case SDL_BUTTON_LEFT:
                beingDragged = false;
                if (mousedOver)
                {
                    if (leftClicked == true)
                    {
                        // left button release event
                        leftReleased = true;
                        leftClicked = false;
                    }
                }

                break;

            case SDL_BUTTON_RIGHT:

                if (mousedOver)
                {
                    if (rightClicked == true)
                    {
                        // right button release event
                        rightReleased = true;
                        rightClicked = false;
                    }
                }

                break;
        }
    }
}

void Button::ToggleAltImage()
{
    usingAltTexture = !usingAltTexture;
}

void Button::Update()
{
    ShowCollisionBox(useCollisionBox && (mousedOver || beingDragged));
}

