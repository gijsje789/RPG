#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <SDL_image.h>
#include "log.h"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void CleanUp() = 0;
};

#endif // GAMEOBJECT_H
