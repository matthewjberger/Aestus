#include "Globals.h"

bool CollisionTest(SDL_Rect A, SDL_Rect B)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;


	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;


	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;


	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}


	return true;
}

bool MARCollisionTest(int mouseX, int mouseY, SDL_Rect B)
{
	if ((mouseX > B.x) && (mouseX < B.x + B.w) && (mouseY > B.y) && (mouseY < B.y + B.h)) // if mouse is inside of box
	{
		return true;
	}

	return false;
}