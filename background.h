#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "gameobject.h"

#include <fstream>

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
    bool LoadMap();
    bool GenerateMap();

    SDL_Texture* mBackGroundTex = nullptr;
    SDL_Surface* mBackGroundSurf = nullptr;

    SDL_PixelFormat* mPixelFormat;

    std::vector<SDL_Surface*> mTiles;
    std::vector<std::vector<int>> mMap;
};

#endif // BACKGROUND_H
