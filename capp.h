#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>

#include "log.h"
#include "background.h"

class CApp
{
public:
    CApp();

    int Execute();
    bool Init();
    void CheckEvent(SDL_Event* pEvent);
    void Update();
    void Render();
    void CleanUp();
private:
    bool mRunning = false;
    static const int WINDOW_W = 1024;
    static const int WINDOW_H = 768;

    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    SDL_Surface* mPrimarySurface = nullptr;

    BackGround* mBackGround = new BackGround("sheet_1616", ".png");
};

#endif // CAPP_H
