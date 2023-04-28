#include "TextureManager.h"

#include "SDL_image.h"


TextureManager::TextureManager()
{
	//Initialize
	mTexture = NULL;
	mRenderer = NULL;

	mWidth = 0;
	mHeight = 0;

	mTileWidth = 0;
	mTileHeight = 0;
}

TextureManager::~TextureManager()
{
	//Deallocate
	Free();
}
SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* surface = IMG_Load(fileName);
	if (!surface)
	{
		std::cerr << SDL_GetError() << " Img_Load in LoadTexture" << std::endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	if (!texture)
	{
		std::cerr << SDL_GetError() << " CreateTextureFromSurface in LoadTexture" << std::endl;
		return nullptr;
	}

	SDL_FreeSurface(surface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, const SDL_Rect& src, const SDL_Rect& dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
void TextureManager::Free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void TextureManager::RenderTile(int centerX, int centerY, int tileNumber, double scale, double angle)
{
	SDL_Rect clipQuad = { mTileWidth * (tileNumber % (mWidth / mTileWidth)),
						  mTileHeight * (tileNumber / (mWidth / mTileWidth)),
						  mTileWidth, mTileHeight };

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { centerX - int(mTileWidth * scale / 2),
							centerY - int(mTileHeight * scale / 2),
							int(mTileWidth * scale), int(mTileHeight * scale) };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, &clipQuad, &renderQuad, angle, NULL, SDL_FLIP_NONE);
}
void TextureManager::SetTileSize(int width, int height)
{
	mTileWidth = width;
	mTileHeight = height;
}
int TextureManager::GetWidth()
{
	return mWidth;
}

int TextureManager::GetHeight()
{
	return mHeight;
}