#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include "log.h"

#define RESOURCE_FOLDER "../RPG/Resources/"

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void Update() = 0;
    virtual void Render(SDL_Renderer* pRenderer) = 0;
    virtual void CleanUp() = 0;
};

#endif // GAMEOBJECT_H
