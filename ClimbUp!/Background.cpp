#include "Background.h"
#include"TextureManager.h"

Background::Background() {
	background = TextureManager::LoadTexture("./assets/background.png");

	src.x = src.y = 0;
	src.w =  1276;
	src.h =  953;
	dest.w = 800;
	dest.h = 640;

	dest.x = dest. y = 0;
}

void Background::DrawBackground()
{
	TextureManager::Draw(background, src, dest);
}
