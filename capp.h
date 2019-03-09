#ifndef CAPP_H
#define CAPP_H

#include <SDL.h>

#include "log.h"
#include "background.h"
#include "foreground.h"

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
    static int Window_W();
    static int Window_H();
private:
    bool mRunning = false;
    static const int WINDOW_W = 1024;
    static const int WINDOW_H = 768;

    SDL_Window* mWindow = nullptr;
    SDL_Renderer* mRenderer = nullptr;
    SDL_Surface* mPrimarySurface = nullptr;

    BackGround* mBackGround = nullptr;
    ForeGround* mForeGround = nullptr;
};

#endif // CAPP_H
