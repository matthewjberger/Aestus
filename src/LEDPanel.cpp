#include "LEDPanel.h"
#include <iostream>

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

        cout << stdImage << endl;
        cout << altImage << endl << endl;

        mButtons[i] = new Button(stdImage, altImage);
    }
}

LEDPanel::~LEDPanel()
{
    for (auto i : mButtons)
    {
        delete i;
    }
}

void LEDPanel::Draw(int x, int y)
{
    for (int i = 0; i < NUM_LEDS; i += NUM_TYPES)
    {
        int offsetY = i * 40 + y + mMargin;

        // Draw the large button
        mButtons[i]->SetX(x + mMargin);
        mButtons[i]->SetY(offsetY);
        mButtons[i]->Draw();

        // Draw the small button
        mButtons[i + 1]->SetX(mButtons[i]->GetCollisionBox().x + mButtons[i]->GetCollisionBox().w + mGap);
        mButtons[i + 1]->SetY(offsetY + mGap);
        mButtons[i + 1]->Draw();

        // Draw the final button
        mButtons[i + 2]->SetX(mButtons[i + 1]->GetCollisionBox().x);
        mButtons[i + 2]->SetY(mButtons[i + 1]->GetCollisionBox().y + mButtons[i + 1]->GetCollisionBox().h + mGap);
        mButtons[i + 2]->Draw();
    }
}

void LEDPanel::HandleEvents()
{
    for(auto i : mButtons)
    {
        i->HandleEvents();

        if(i->IsBeingDragged())
        {
            for(auto j : mButtons)
            {
                j->UseCollisionBox(false);
            }

            i->UseCollisionBox(true);

            mButtonBeingDragged = true;
        }

        if(i->WasLeftClicked())
        {
            if(mButtonActive && i->UsingAltImage())
            {
                mButtonActive = false;
            }
            else if(mButtonActive && !i->UsingAltImage())
            {
                for(auto j : mButtons)
                {
                    if(j->UsingAltImage()) j->ShowAltImage(false);
                }

            }
            else if(!mButtonActive)
            {
                mButtonActive = true;
            }

            i->ToggleAltImage();
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
    }

}

