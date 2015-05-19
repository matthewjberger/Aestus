#include "PresentationState.h"
#include "Globals.h"

PresentationState *PresentationState::inst = 0;

void PresentationState::Init()
{
	printf("Intro Init\n");

    ledPanel = new LEDPanel();
}

void PresentationState::Finalize()
{
	printf("Intro Finalize\n");

	delete ledPanel;
}

void PresentationState::Draw()
{
    Game *game = Game::GetInstance();

    game->ClearScreen(101, 156, 239);
    ledPanel->Draw();
}

void PresentationState::Update()
{
}

void PresentationState::HandleEvents()
{
    ledPanel->HandleEvents();
}

void PresentationState::Pause()
{
	printf("Intro Paused\n");
}

void PresentationState::Resume()
{
	printf("Intro Resumed\n");
}
