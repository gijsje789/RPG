#include "background.h"

BackGround::BackGround(std::string pFile, std::string pExtension, SDL_PixelFormat* pPixelFormat)
    : mPixelFormat(pPixelFormat){
    // TODO: Set up a map using smaller sprites.
    // TODO: make map of smaller tiles.
    std::string filePath = "../RPG/Resources/" + pFile + pExtension;
    SDL_Surface* spriteSheet = IMG_Load(filePath.c_str());

    if(spriteSheet == nullptr) {
        Log("Nullpointer received.");
    }

    Log("Size spritesheet: %d %d", spriteSheet->w, spriteSheet->h);

    GetTilesFromSpriteSheet(spriteSheet, 16, 16);

    LoadMap();

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
    // FIXME: clean up
    mBackGroundTex = SDL_CreateTextureFromSurface(pRenderer, mBackGroundSurf);
    if(mBackGroundTex == nullptr) {
        Log("Unable to create background texture: %s", SDL_GetError());
    } else if (SDL_RenderCopy(pRenderer, mBackGroundTex, nullptr, nullptr)) {
        Log("Unable to render background: %s", SDL_GetError());
    }
}

void BackGround::CleanUp()
{
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

bool BackGround::LoadMap()
{
    std::ifstream myfile;
    myfile.open("../RPG/Resources/background.csv");
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
    Log("Map size: (%d, %d)(w,h).", mMap[0].size(), mMap.size());
    return true;
}

bool BackGround::GenerateMap()
{
    SDL_Surface* background = SDL_CreateRGBSurface(0, 1024, 768, 32, 0,0,0,0);
    SDL_Rect rect;
    rect.w = 16;
    rect.h = 16;
    for(int y = 0; y < static_cast<int>(mMap.size()); y++) {
        for(int x = 0; x < static_cast<int>(mMap.at(y).size()); x++) {
            rect.x = x*16;
            rect.y = y*16;
            if(SDL_BlitSurface(mTiles[mMap.at(y).at(x)], nullptr, background, &rect) != 0) {
                Log("Error blitting surface to background: %s", SDL_GetError());
                return false;
            }
        }
    }
    mBackGroundSurf = background;
    return true;
}
