#ifndef FOREGROUND_H
#define FOREGROUND_H

#include "map.h"

class ForeGround : public Map
{
public:
    ForeGround(std::string pSpriteSheet, std::string pMap);
    ~ForeGround();

    void Update();
    void Render(SDL_Renderer* pRenderer);
    void CleanUp();
};

#endif // FOREGROUND_H
