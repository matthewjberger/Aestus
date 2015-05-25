#include "CTexture.h"
#include "CoreGame.h"

Texture::Texture()
{
	// Initialize variables
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mShowCollisionBox = false;
}

Texture::~Texture()
{
	// Deallocate
	Free();
}

void Texture::LoadImage(string path)
{
	// Get game instance
	Game *game = Game::GetInstance();

	// Unbind and deallocate any texture already bound
	Free();

	// final texture
	SDL_Texture* finalTexture = NULL;

	// Load image
	SDL_Surface* initialSurface = IMG_Load(path.c_str());

	if (initialSurface == NULL)
	{
		printf("Unable to load image %s", path.c_str());
		printf("SDL_Error: %s", SDL_GetError());

		game->StopRunning();
	}
	else
	{
		// Set Color Key (cyan)
		SDL_SetColorKey(initialSurface, SDL_TRUE, SDL_MapRGB(initialSurface->format, 0, 0xFF, 0xFF));

		// Create texture from initialSurface pixels
		finalTexture = SDL_CreateTextureFromSurface(game->GetRenderer(), initialSurface);

		if (finalTexture == NULL)
		{
			printf("Unable to create texture from %s", path.c_str());
			printf("SDL_Error: %s", SDL_GetError());

			game->StopRunning();
		}
		else
		{
			mWidth = initialSurface->w;
			mHeight = initialSurface->h;
		}

		// Discard initial surface
		SDL_FreeSurface(initialSurface);
	}

	// Set member texture to optimized texture
	mTexture = finalTexture;
}

void Texture::LoadText(string text, SDL_Color textColor, TTF_Font* font)
{
	// Get game instance
	Game *game = Game::GetInstance();

	// Unbind and deallocate any texture already bound
	Free();

	// Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s", TTF_GetError());

		game->StopRunning();
	}
	else
	{
		// Create texture from pixels on surface
		mTexture = SDL_CreateTextureFromSurface(game->GetRenderer(), textSurface);

		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL_ttf Error: %s", SDL_GetError());

			game->StopRunning();
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Discard old surface
		SDL_FreeSurface(textSurface);
	}
}

void Texture::Free()
{
	// Free any existing texture
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);

		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::Draw(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	// Get game instance
	Game *game = Game::GetInstance();

	// Set rendering area
	SDL_Rect renderArea = { x, y, mWidth, mHeight };

	// Set clip dimensions
	if (clip != NULL)
	{
		renderArea.w = clip->w;
		renderArea.h = clip->h;
	}

	if(mShowCollisionBox)
    {
        SDL_SetRenderDrawColor( game->GetRenderer(), 0, 255, 0, 255);
        SDL_RenderDrawRect(game->GetRenderer(), &renderArea);
    }

	// Render to screen
	SDL_RenderCopyEx(game->GetRenderer(), mTexture, clip, &renderArea, angle, center, flip);
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture color
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}
