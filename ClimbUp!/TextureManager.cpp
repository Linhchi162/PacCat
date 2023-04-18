#include"TextureManager.h"

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
