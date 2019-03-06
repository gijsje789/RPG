#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "gameobject.h"

class BackGround : public GameObject
{
public:
    BackGround(std::string pFile, std::string pExtension, SDL_PixelFormat* pPixelFormat);
    ~BackGround();

    void Update();
    void Render(SDL_Renderer* pRenderer);
    void CleanUp();
private:
    bool GetTilesFromSpriteSheet(SDL_Surface* pSpriteSheet, int pTile_w, int pTile_h);

    SDL_Surface* mSpriteSheet = nullptr;
    SDL_Texture* mBackGroundTex = nullptr;

    SDL_PixelFormat* mPixelFormat;

    std::vector<SDL_Surface*> mTiles;
};

#endif // BACKGROUND_H
