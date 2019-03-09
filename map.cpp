#include "map.h"

#include "capp.h"

Map::Map(std::string pSpriteSheet, std::string pMap)
{
    // TODO: Create nicer map.
    std::string filePath = RESOURCE_FOLDER + pSpriteSheet;
    SDL_Surface* spriteSheet = IMG_Load(filePath.c_str());
    Log("%s", SDL_GetPixelFormatName(spriteSheet->format->format));
    if(spriteSheet == nullptr) {
        Log("Nullpointer received.");
    }

    Log("Size spritesheet: %d %d", static_cast<int>(spriteSheet->w), static_cast<int>(spriteSheet->h));

    GetTilesFromSpriteSheet(spriteSheet, std::stoi(pSpriteSheet.substr(pSpriteSheet.find('_')+1, 2)), std::stoi(pSpriteSheet.substr(pSpriteSheet.find('_')+3, 2)));
    // TODO: get csv name from function call
    LoadMap(pMap);

    mSurface = SDL_CreateRGBSurface(0, CApp::Window_W(), CApp::Window_H(), 32, 0xff, 0xff00, 0xff0000, 0xff000000);

    GenerateMap(mMap, mTiles, mSurface);
}

Map::~Map()
{

}

void Map::CleanUp()
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

bool Map::GetTilesFromSpriteSheet(SDL_Surface *pSpriteSheet, int pTile_w, int pTile_h)
{
    if(pSpriteSheet->w % pTile_w == 0 && pSpriteSheet->h % pTile_h == 0) {
        SDL_Rect srcRect;
        srcRect.w = pTile_w;
        srcRect.h = pTile_h;
        for(int y = 0; y < pSpriteSheet->h / pTile_h; y++) {
            for(int x = 0; x < pSpriteSheet->w / pTile_w; x++) {
                srcRect.x = x*pTile_w;
                srcRect.y = y*pTile_h;
                SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, pTile_w, pTile_h, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
                if(SDL_BlitSurface(pSpriteSheet, &srcRect, tempSurface, nullptr)==0) {
                    mTiles.push_back(tempSurface);
                } else {
                    Log("Error extracting tile (%d,%d)(w,h): %s", x, y, SDL_GetError());
                    return false;
                }
            }
        }
        Log("Number of tiles: %d", static_cast<int>(mTiles.size()));
    } else {
        Log("Background spritesheet is incompatible with tile dimensions (%d,%d)(w,h).", pTile_w, pTile_h);
        return false;
    }
    return true;
}

bool Map::LoadMap(std::string pFile)
{
    std::ifstream myfile;
    myfile.open(RESOURCE_FOLDER + pFile);
    std::string line;

    if(myfile.is_open()) {
        while(std::getline(myfile, line) && !myfile.eof()) {
            std::vector<int> temp;
            std::string buffer = "";
            for(char &chr : line) {
                if(chr == ',') {
                    temp.push_back(static_cast<int>(std::stoi(buffer)));
                    buffer.clear();
                } else {
                    buffer += chr;
                }
            }
            if(!buffer.empty()) temp.push_back(static_cast<int>(std::stoi(buffer)));
            mMap.push_back(temp);
        }
    } else {
        Log("Unable to open background file.");
        return false;
    }
    mDstTile_W = (static_cast<int>(CApp::Window_W())/static_cast<int>(mMap[0].size()));
    mDstTile_H = static_cast<int>(static_cast<int>(CApp::Window_H())/static_cast<int>(mMap.size()));
    Log("Map size: (%d, %d)(w,h).", static_cast<int>(mMap[0].size()), static_cast<int>(mMap.size()));
    return true;
}

bool Map::GenerateMap(std::vector<std::vector<int>> &pMap, std::vector<SDL_Surface*> &pTiles, SDL_Surface* pDestination)
{
    SDL_Rect rect;
    rect.w = mDstTile_W;
    rect.h = mDstTile_H;
    SDL_Surface* transparent = SDL_CreateRGBSurface(0, mDstTile_W, mDstTile_H, 32, 0xff, 0xff00, 0xff0000, 0xff000000);

    for(int y = 0; y < static_cast<int>(pMap.size()); y++) {
        for(int x = 0; x < static_cast<int>(pMap.at(static_cast<unsigned long>(y)).size()); x++) {
            rect.x = x*mDstTile_W;
            rect.y = y*mDstTile_H;
            int index = static_cast<int>(pMap.at(static_cast<unsigned long>(y)).at(static_cast<unsigned long>(x)));
            if(index < 0) {
                if(SDL_BlitScaled(transparent, nullptr, pDestination, &rect) != 0) {
                    Log("Error blitting transparent surface to destination: %s", SDL_GetError());
                }
            } else if(SDL_BlitScaled(pTiles[static_cast<unsigned long>(index)],
                              nullptr, pDestination, &rect) != 0) {
                Log("Error blitting surface to destination: %s", SDL_GetError());
                return false;
            }
        }
    }
    SDL_FreeSurface(transparent);
    return true;
}
