#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
	// create a temp surface
	SDL_Surface* tmp_surface = IMG_Load(texture);

	// create texture out of the surface 
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmp_surface);

	// clear the temporary surface after use
	SDL_FreeSurface(tmp_surface);

	// return the texture
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip)
{
	//SDL_RenderCopy(Game::renderer, tex, &srcRect, &destRect);

	// SDL_RenderCopyEx gives extra features that 
	// SDL_RenderCopy does not give. 
	// that is very helpful to flip sprites
	SDL_RenderCopyEx(Game::renderer, tex, &srcRect, &destRect, NULL, NULL, flip);
}