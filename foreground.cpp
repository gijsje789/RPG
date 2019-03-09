#include "foreground.h"

ForeGround::ForeGround(std::string pSpriteSheet, std::string pMap) :
    Map(pSpriteSheet, pMap)
{

}

ForeGround::~ForeGround()
{

}

void ForeGround::Update()
{

}

void ForeGround::Render(SDL_Renderer* pRenderer)
{
    if(mTexture) SDL_DestroyTexture(mTexture);
    mTexture = SDL_CreateTextureFromSurface(pRenderer, mSurface);

    if(mTexture == nullptr) {
        Log("Unable to create foreground texture: %s", SDL_GetError());
    } else if (SDL_RenderCopy(pRenderer, mTexture, nullptr, nullptr)) {
        Log("Unable to render foreground: %s", SDL_GetError());
    }
}

void ForeGround::CleanUp()
{
    Map::CleanUp();
}
