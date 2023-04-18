#pragma once
#include"Game.h"



class TextureManager {

public:
	TextureManager();
	~TextureManager();

	bool LoadFromFile(SDL_Renderer* mainRenderer, std::string path, Uint8 fromR = 0xFF, Uint8 fromG = 0xFF, Uint8 fromB = 0xFF,
		Uint8 setR = 0xFF, Uint8 setG = 0xFF, Uint8 setB = 0xFF);


	bool SetColorModeTo(Uint8 r, Uint8 g, Uint8 b);



	void Free();

	void Render(int centerX, int centerY, SDL_Rect* clip = NULL, double scale = 1.0);
	void RenderTile(int centerX, int centerY, int tileNumber, double scale = 1.0, double angle = 0.0);

	void SetTileSize(int width, int height);


	int GetWidth();
	int GetHeight();


private:
	SDL_Texture* mTexture;
	SDL_Renderer* mRenderer;

	int mTileWidth;
	int mTileHeight;

	int mWidth;
	int mHeight;
};

