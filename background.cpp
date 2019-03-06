#include "background.h"

BackGround::BackGround(std::string pFile, std::string pExtension, SDL_PixelFormat* pPixelFormat)
    : mPixelFormat(pPixelFormat){
    // TODO: Set up a map using smaller sprites.
    // TODO: make map of smaller tiles.
    // TODO: refactor such that spritesheet is not stored in memory.
    std::string filePath = "../RPG/Resources/" + pFile + pExtension;
    mSpriteSheet = IMG_Load(filePath.c_str());

    if(mSpriteSheet == nullptr) {
        Log("Nullpointer received.");
    }

    Log("Size spritesheet: %d %d", mSpriteSheet->w, mSpriteSheet->h);

    GetTilesFromSpriteSheet(mSpriteSheet, 16, 16);
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{

}

void BackGround::Render(SDL_Renderer* pRenderer)
{
    // FIXME: clean up

    SDL_Rect rect;
    rect.w = 16;
    rect.h = 16;
    rect.y = 0;
    rect.x = 0;

    SDL_Texture* tex = SDL_CreateTextureFromSurface(pRenderer, mTiles.at(50));
    if(tex == nullptr) {
        Log("Unable to create tile tex: %s", SDL_GetError());
    } else if(SDL_RenderCopy(pRenderer, tex, nullptr, &rect)) {
        Log("unable to render background tile: %s.", SDL_GetError());
    }
    SDL_DestroyTexture(tex);
    /*
    mBackGroundTex = SDL_CreateTextureFromSurface(pRenderer, mSpriteSheet);
    if(mBackGroundTex == nullptr) {
        Log("Unable to create background texture: %s", SDL_GetError());
    } else if (SDL_RenderCopy(pRenderer, mBackGroundTex, nullptr, nullptr)) {
        Log("Unable to render background: %s", SDL_GetError());
    } */
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

bool BackGround::GetTilesFromSpriteSheet(SDL_Surface *pSpriteSheet, int pTile_w, int pTile_h)
{
    if(pSpriteSheet->w % pTile_w == 0 && pSpriteSheet->h % pTile_h == 0) {
        SDL_Rect srcRect;
        srcRect.w = pTile_w;
        srcRect.h = pTile_h;
        for(int y = 0; y < pSpriteSheet->h / pTile_h; y++) {
            for(int x = 0; x < pSpriteSheet->w / pTile_w; x++) {
                srcRect.x = x*pTile_w;
                srcRect.y = y*pTile_h;
                SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, 16, 16, 32, 0, 0, 0, 0);

                if(SDL_BlitSurface(pSpriteSheet, &srcRect, tempSurface, nullptr)==0) {
                    mTiles.push_back(tempSurface);
                } else {
                    Log("Error extracting tile (%d,%d)(w,h): %s", x, y, SDL_GetError());
                    return false;
                }
            }
        }
    } else {
        Log("Background spritesheet is incompatible with tile dimensions (%d,%d)(w,h).", pTile_w, pTile_h);
        return false;
    }
    return true;
}
