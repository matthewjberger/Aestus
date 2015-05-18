#include "PresentationState.h"
#include "Globals.h"

PresentationState *PresentationState::inst = 0;

void PresentationState::Init()
{
	printf("Intro Init\n");

	mButton = new Button(0,0,"Images/PL-B-I.png","Images/PL-B-O.png");
}

void PresentationState::Finalize()
{
	printf("Intro Finalize\n");

    delete mButton;
}

void PresentationState::Draw()
{
    mButton->Draw();
}

void PresentationState::Update()
{
}

void PresentationState::HandleEvents()
{
    mButton->HandleEvents();

    if(mButton->WasLeftClicked())
    {
        mButton->ToggleAltImage();
    }
}

void PresentationState::Pause()
{
	printf("Intro Paused\n");
}

void PresentationState::Resume()
{
	printf("Intro Resumed\n");
}

