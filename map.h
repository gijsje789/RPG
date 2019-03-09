#ifndef MAP_H
#define MAP_H

#include <fstream>

#include "gameobject.h"

class CApp;

class Map : public GameObject
{
public:
    Map(std::string pSpriteSheet, std::string pMap);
    ~Map();
    void CleanUp();
protected:
    bool GetTilesFromSpriteSheet(SDL_Surface* pSpriteSheet, int pTile_w, int pTile_h);
    bool LoadMap(std::string pFile);
    bool GenerateMap(std::vector<std::vector<int>> &pMap, std::vector<SDL_Surface*> &pTiles, SDL_Surface* pDestination);

    SDL_Surface* mSurface = nullptr;
    SDL_Texture* mTexture = nullptr;

    std::vector<SDL_Surface*> mTiles;
    std::vector<std::vector<int>> mMap;

    int mDstTile_W = -1;
    int mDstTile_H = -1;
};

#endif // MAP_H
