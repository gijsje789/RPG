#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "gameobject.h"

class BackGround : public GameObject
{
public:
    BackGround(std::string pFile, std::string pExtension);
    ~BackGround();

    void Update();
    void Render(SDL_Renderer* pRenderer);
    void CleanUp();
private:
    SDL_Surface* mSpriteSheet = nullptr;
    SDL_Texture* mBackGroundTex = nullptr;
};

#endif // BACKGROUND_H
