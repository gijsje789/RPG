#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "map.h"

class BackGround : public Map
{
public:
    BackGround(std::string pFile, std::string pExtension);
    ~BackGround();

    void Update();
    void Render(SDL_Renderer* pRenderer);
    void CleanUp();
protected:
    //bool GetTilesFromSpriteSheet(SDL_Surface* pSpriteSheet, int pTile_w, int pTile_h);
    //bool LoadMap(std::string pFile, std::string pExtension);
    //bool GenerateMap(std::vector<std::vector<int>> &pMap, std::vector<SDL_Surface*> &pTiles, SDL_Surface* pDestination);
};

#endif // BACKGROUND_H
