#include "background.h"

BackGround::BackGround(std::string pFile, std::string pExtension, SDL_PixelFormat* pPixelFormat)
    : mPixelFormat(pPixelFormat){
    // TODO: Create nicer map.
    std::string filePath = "../RPG/Resources/" + pFile + pExtension;
    SDL_Surface* spriteSheet = IMG_Load(filePath.c_str());

    if(spriteSheet == nullptr) {
        Log("Nullpointer received.");
    }

    Log("Size spritesheet: %d %d", spriteSheet->w, spriteSheet->h);

    GetTilesFromSpriteSheet(spriteSheet, 16, 16);

    LoadMap("background", ".csv");

    GenerateMap();
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{

}

void BackGround::Render(SDL_Renderer* pRenderer)
{
    // TODO: have texture loaded in class memory.
    mBackGroundTex = SDL_CreateTextureFromSurface(pRenderer, mBackGroundSurf);
    if(mBackGroundTex == nullptr) {
        Log("Unable to create background texture: %s", SDL_GetError());
    } else if (SDL_RenderCopy(pRenderer, mBackGroundTex, nullptr, nullptr)) {
        Log("Unable to render background: %s", SDL_GetError());
    }
}

void BackGround::CleanUp()
{
    if(mBackGroundSurf) {
        SDL_FreeSurface(mBackGroundSurf);
        mBackGroundSurf = nullptr;
    }

    if(mBackGroundTex) {
        SDL_DestroyTexture(mBackGroundTex);
        mBackGroundTex = nullptr;
    }

    for(SDL_Surface* surface : mTiles) {
        if(surface) {
            SDL_FreeSurface(surface);
            surface = nullptr;
        }
    }
    mTiles.clear();

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

// TODO: make it more flexible by having the file as parameter.
bool BackGround::LoadMap(std::string pFile, std::string pExtension)
{
    std::ifstream myfile;
    myfile.open(RESOURCE_FOLDER + pFile + pExtension);
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
            mMap.push_back(temp);
        }
    } else {
        Log("Unable to open background file.");
        return false;
    }
    Log("Map size: (%d, %d)(w,h).", static_cast<int>(mMap[0].size()), static_cast<int>(mMap.size()));
    return true;
}

// TODO: make the generation more flexible by having the map and tile sizes as parameters.
bool BackGround::GenerateMap()
{
    SDL_Surface* background = SDL_CreateRGBSurface(0, 1024, 768, 32, 0,0,0,0);
    SDL_Rect rect;
    rect.w = 16;
    rect.h = 16;
    for(int y = 0; y < static_cast<int>(mMap.size()); y++) {
        for(int x = 0; x < static_cast<int>(mMap.at(static_cast<unsigned long>(y)).size()); x++) {
            rect.x = x*16;
            rect.y = y*16;
            if(SDL_BlitSurface(mTiles[static_cast<unsigned long>(mMap.at(static_cast<unsigned long>(y)).at(static_cast<unsigned long>(x)))],
                               nullptr, background, &rect) != 0) {
                Log("Error blitting surface to background: %s", SDL_GetError());
                return false;
            }
        }
    }
    mBackGroundSurf = background;
    return true;
}
