#ifndef GLOBALS_H
#define GLOBALS_H

#define PI 3.1415

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"
#include "CTexture.h"
#include "CButton.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;

// Particle System
const int TOTAL_PARTICLES = 200;

// SNOW
const int drift = 0;

// Button types
enum ButtonTypes
{
	IMAGE = 1,  // button used the constructor with an image
	TEXT = 2  // button used the constructor with text
};
// Particle systems
enum
{
	NONE      = 0,
	STARFIELD = 1,
	SNOW      = 2,
	MATRIX    = 3
};

// Axix aligned bounding box collision test
extern bool CollisionTest(SDL_Rect A, SDL_Rect B);

// Mouse and Rectangle collision test
extern bool MARCollisionTest(int mouseX, int mouseY, SDL_Rect B);

#endif
