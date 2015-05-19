#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <vector>

using namespace std;

// SDL_Texture wrapper class
class Texture
{
public:
	Texture();
	~Texture();

	// loads/binds image to texture
	void LoadImage(string path);

	// loas/binds text to texture
	void LoadText(string text, SDL_Color textColor, TTF_Font* font);

	// Deallocates texture
	void Free();

	// Renders texture
	void Draw(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Set Color modulation
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void SetBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void SetAlpha(Uint8 alpha);

	// Gets image dimensions
	int GetWidth()
	{
		return mWidth;
	}

	int GetHeight()
	{
		return mHeight;
	}

    // Collision Box Visibility setting
    void SetCollisionBoxVisible(bool vis) { mShowCollisionBox = vis; }

	// Toggle collision box visibility
	void ToggleCollisionBox() { mShowCollisionBox = !mShowCollisionBox; }

private:
	// Hardware texture
	SDL_Texture *mTexture;

	// Dimensions
	int mWidth;
	int mHeight;

	// Collision box debugging
	bool mShowCollisionBox;

};
