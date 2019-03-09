#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "map.h"

class BackGround : public Map
{
public:
    BackGround(std::string pSpriteSheet, std::string pMap);
    ~BackGround();

    void Update();
    void Render(SDL_Renderer* pRenderer);
    void CleanUp();
protected:

};

#endif // BACKGROUND_H
