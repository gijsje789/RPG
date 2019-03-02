#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "gameobject.h"

class BackGround : public GameObject
{
public:
    BackGround();
    ~BackGround();

    void Update();
    void Render();
    void CleanUp();
private:
    SDL_Surface* mSpriteSheet = nullptr;
};

#endif // BACKGROUND_H
