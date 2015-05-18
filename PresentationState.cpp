#include "PresentationState.h"
#include "Globals.h"

PresentationState *PresentationState::inst = 0;

void PresentationState::Init()
{
	printf("Intro Init\n");
}

void PresentationState::Finalize()
{
	printf("Intro Finalize\n");
}

void PresentationState::Draw()
{
}

void PresentationState::Update()
{
}

void PresentationState::HandleEvents()
{
}

void PresentationState::Pause()
{
	printf("Intro Paused\n");
}

void PresentationState::Resume()
{
	printf("Intro Resumed\n");
}

