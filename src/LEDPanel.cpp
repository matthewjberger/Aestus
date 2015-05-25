#include "LEDPanel.h"
#include "CoreGame.h"
#include <iostream>

Game* game = Game::GetInstance();

LEDPanel::LEDPanel()
{
    mMargin = 10;
    mGap    = 15;
    mButtonActive = false;
    mButtonBeingDragged = false;

    string type[]  = {"TH", "PL", "SM"};
    string color[] = {"R", "O", "Y", "G", "B", "W" };

    for(int i = 0; i < NUM_LEDS; i++)
    {
        string baseName = "Images/" + type[i%3] + "-" + color[i/3];
        string stdImage = baseName + "-O.png";
        string altImage = baseName + "-I.png";

        mButtons[i] = new Button(stdImage, altImage);
    }

    mSlider = new Slider(240,25,2,(game->GetScreenHeight() - 50));
}

LEDPanel::~LEDPanel()
{
    for (auto i : mButtons)
    {
        delete i;
    }

    delete mSlider;
}

void LEDPanel::Draw(int x, int y)
{
    for (int i = 0; i < NUM_LEDS; i += NUM_TYPES)
    {
        int offsetY = i * 40 + y + mMargin;

        Button *bigBtn     = mButtons[i];
        Button *mediumBtn  = mButtons[i + 1];
        Button *smallBtn   = mButtons[i + 2];

        // Draw the large button
        bigBtn->SetX(x + mMargin);
        bigBtn->SetY(offsetY);
        bigBtn->Draw();

        // Draw the medium button
        mediumBtn->SetX(bigBtn->GetCollisionBox().x + bigBtn->GetCollisionBox().w + mGap);
        mediumBtn->SetY(offsetY + mGap);
        mediumBtn->Draw();

        // Draw the small button
        smallBtn->SetX((mediumBtn->GetCollisionBox().x + mediumBtn->GetCollisionBox().w/2) - smallBtn->GetCollisionBox().w/2);
        smallBtn->SetY(mediumBtn->GetCollisionBox().y + mediumBtn->GetCollisionBox().h + mGap);
        smallBtn->Draw();

        bigBtn    = NULL;
        mediumBtn = NULL;
        smallBtn  = NULL;
    }

    mSlider->Draw();
}

void LEDPanel::HandleEvents()
{
    Game *game = Game::GetInstance();

    SDL_Event event = game->GetEvent();

    for(auto i : mButtons)
    {
        i->HandleEvents();

        // if a button was left clicked
        if(i->WasLeftClicked())
        {
            // There is a lit button and this one is it
            if(mButtonActive && i->UsingAltImage())
            {
                // Disable it
                mButtonActive = false;
            }
            else if(mButtonActive && !i->UsingAltImage())
            {
                // There is a lit button and this one is not it
                for(auto j : mButtons)
                {
                    // Find the one that is using the alt image and disable it
                    if(j->UsingAltImage()) j->ShowAltImage(false);
                }

            }
            // If no button is active, set the flag
            else if(!mButtonActive)
            {
                mButtonActive = true;
            }

            // Always toggle the image upon clicking
            i->ToggleAltImage();
        }
    }

    mSlider->HandleEvents();

    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_l:
                mSlider->ToggleLock();
                break;
        }
    }
}

void LEDPanel::Update()
{
    for(auto i : mButtons)
    {
        // Allow only one button to be highlighted at a time
        i->Update();

        i->UseCollisionBox(true);

        mButtonBeingDragged = false;

        // If a button is being dragged
        if(i->IsBeingDragged())
        {
            // Disable all collision boxes
            for(auto j : mButtons)
            {
                j->UseCollisionBox(false);
            }

            // Enable just the one that's being dragged
            i->UseCollisionBox(true);

            // Set the flag
            mButtonBeingDragged = true;
        }
    }

    mSlider->Update();
}

