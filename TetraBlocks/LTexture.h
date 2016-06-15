#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(SDL_Renderer* gRenderer, std::string path);

	//Creates image from font string
	bool loadFromRenderedText(SDL_Renderer* gRenderer, std::string textureText, SDL_Color textColor);
	bool loadFromRenderedText(SDL_Renderer* gRenderer, std::string textureText);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void SetFont(TTF_Font* font);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Global Font Reference
	TTF_Font* gFont;

	//Image dimensions
	int mWidth;
	int mHeight;
};