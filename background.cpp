#include "background.h"

BackGround::BackGround(std::string pFile, std::string pExtension)
{
    // TODO: relative resource path.
    // TODO: Set up a map using smaller sprites.
    std::string filePath = "C:/Users/gijsj/Documents/QT/RPG/Resources/" + pFile + pExtension;
    mSpriteSheet = IMG_Load(filePath.c_str());
    if(mSpriteSheet == nullptr) Log("Nullpointer received.");
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{

}

void BackGround::Render(SDL_Renderer* pRenderer)
{
    mBackGroundTex = SDL_CreateTextureFromSurface(pRenderer, mSpriteSheet);
    if(mBackGroundTex == nullptr) {
        Log("Unable to create background texture: %s", SDL_GetError());
    } else if (SDL_RenderCopy(pRenderer, mBackGroundTex, nullptr, nullptr)) {
        Log("Unable to render background: %s", SDL_GetError());
    }
}

void BackGround::CleanUp()
{
    if(mSpriteSheet) {
        SDL_FreeSurface(mSpriteSheet);
        mSpriteSheet = nullptr;
    }

    if(mBackGroundTex) {
        SDL_DestroyTexture(mBackGroundTex);
        mBackGroundTex = nullptr;
    }
}
