#include "background.h"

BackGround::BackGround(std::string pSpriteSheet, std::string pMap) :
    Map(pSpriteSheet, pMap)
{

}

BackGround::~BackGround()
{

}

void BackGround::Update()
{

}

void BackGround::Render(SDL_Renderer* pRenderer)
{
    if(mTexture) SDL_DestroyTexture(mTexture);
    mTexture = SDL_CreateTextureFromSurface(pRenderer, mSurface);

    if(mTexture == nullptr) {
        Log("Unable to create background texture: %s", SDL_GetError());
    } else if (SDL_RenderCopy(pRenderer, mTexture, nullptr, nullptr)) {
        Log("Unable to render background: %s", SDL_GetError());
    }
}

void BackGround::CleanUp()
{
    if(mSurface) {
        SDL_FreeSurface(mSurface);
        mSurface = nullptr;
    }

    if(mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }

    for(SDL_Surface* surface : mTiles) {
        if(surface) {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }
    mTiles.clear();

}


