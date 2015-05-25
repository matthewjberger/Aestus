#include "Slider.h"
#include "CoreGame.h"

Slider::Slider(int x, int y, int w, int h, int boundOffset)
{

    mLocked = false;
    mIncrement = 10;

    mFillRect.x = x;
    mFillRect.y = y;
    mFillRect.w = w;
    mFillRect.h = h;

    mColRect.x = x - boundOffset;
    mColRect.y = y;
    mColRect.w = w + 2*boundOffset;
    mColRect.h = h;

    cout << "mFillRect.x = " << x << endl;
    cout << "mFillRect.y = " << y << endl;
    cout << "mFillRect.w = " << w << endl;
    cout << "mFillRect.h = " << h << endl;

    // Create and center button
    mButton = new Button(0, 0, "                  ", 12);
    mButton->SetX(mFillRect.x + mFillRect.w/2 - mButton->GetCollisionBox().w/2);

    // Begin at 50%
    mButton->SetY((mFillRect.y + mFillRect.h)/2);
    mButton->UseHoverHighlight(false);

}

Slider::~Slider()
{
    delete mButton;
}

void Slider::Draw()
{
    Game* game = Game::GetInstance();

    SDL_SetRenderDrawColor(game->GetRenderer(), 255, 255, 255, 255);
    SDL_RenderFillRect(game->GetRenderer(), &mFillRect);

    // Draw collision rect
    //SDL_SetRenderDrawColor(game->GetRenderer(), 255, 255, 255, 255);
    //SDL_RenderDrawRect(game->GetRenderer(), &mColRect);

    mButton->Draw();
}

void Slider::HandleEvents()
{
    Game *game = Game::GetInstance();
    SDL_Event event = game->GetEvent();

    if(!mLocked)
    {
        mButton->HandleEvents();

        int x, y;
        SDL_GetMouseState(&x, &y);

        // Allow user to drag slider to position
        if(mButton->IsBeingDragged())
        {
            mButton->SetY(y - mButton->GetCollisionBox().h/2);
        }

        // Allow user to click where they want the slider to be
        if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LMASK && MARCollisionTest(x, y, mColRect))
        {
            mButton->SetY(y - mButton->GetCollisionBox().h/2);
        }

        // Allow arrow keys
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                    mButton->SetY(mButton->GetCollisionBox().y - mIncrement);
                    break;

                case SDLK_DOWN:
                    mButton->SetY(mButton->GetCollisionBox().y + mIncrement);
                    break;
            }
        }

        // Finally, allow the user to use their scrollwheel to change the slider
        else if(event.type == SDL_MOUSEWHEEL)
        {
            if(event.wheel.y > 0)
                    mButton->SetY(mButton->GetCollisionBox().y - mIncrement);
            else if(event.wheel.y < 0)
                    mButton->SetY(mButton->GetCollisionBox().y + mIncrement);
        }
    }
}

void Slider::Update()
{
    if(!mLocked)
    {
        mButton->Update();

        // Keep the button in bounds
        if(mButton->GetCollisionBox().y < mFillRect.y - mButton->GetCollisionBox().h/2)
            mButton->SetY(mFillRect.y - mButton->GetCollisionBox().h/2);

        if(mButton->GetCollisionBox().y > mFillRect.y + mFillRect.h - mButton->GetCollisionBox().h/2)
            mButton->SetY(mFillRect.y + mFillRect.h - mButton->GetCollisionBox().h/2);

        GetPercentage();
    }
}

int Slider::GetPercentage()
{
    int partial = (mButton->GetCollisionBox().y + mButton->GetCollisionBox().h/2) - mFillRect.y;
    int whole   = mFillRect.h;
    int percentage = 100 - (100 * partial / whole);

    cout << partial << " " << whole << " " << percentage << endl;

    return percentage;
}
