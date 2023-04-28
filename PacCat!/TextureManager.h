#pragma once

#include "Game.h"

class TextureManager {
public:
	TextureManager();
	~TextureManager();
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest);

	void RenderTile(int centerX, int centerY, int tileNumber, double scale = 1.0, double angle = 0.0);

	void SetTileSize(int width, int height);
	void Free();

	int GetWidth();
	int GetHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;

	int mTileWidth;
	int mTileHeight;

	//Image dimensions
	int mWidth;
	int mHeight;
};
