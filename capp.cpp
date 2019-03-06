#include "capp.h"

CApp::CApp()
{

}

int CApp::Execute()
{
    if(!Init()) return -1;

    SDL_Event Event;

    while(mRunning) {

        while(SDL_PollEvent(&Event)) {
            CheckEvent(&Event);
        }

        Update();
        Render();

        SDL_Delay(1);
    }

    CleanUp();

    return 0;
}

bool CApp::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Log("Unable to initialise SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("RPG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    if(mWindow == nullptr) {
        Log("Unable to create window: %s", SDL_GetError());
        return false;
    }

    mPrimarySurface = SDL_GetWindowSurface(mWindow);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    if(mRenderer == nullptr) {
        Log("Unable to create renderer: %s", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

    mBackGround = new BackGround("sheet_1616", ".png", mPrimarySurface->format);

    mRunning = true;
    return true;
}

void CApp::CheckEvent(SDL_Event* pEvent)
{
    if(pEvent->type == SDL_QUIT) {
        mRunning = false;
    }

    if(pEvent->type == SDL_MOUSEMOTION) {
        // Log("Mouse, X: %d, Y: %d", pEvent->motion.x, pEvent->motion.y);
    }

    if(pEvent->type == SDL_MOUSEBUTTONDOWN) {
        // Log("Mouse down, X: %d, Y: %d", pEvent->button.x, pEvent->button.y);
    }

    if(pEvent->type == SDL_MOUSEBUTTONUP) {
        // Log("Mouse up, X: %d, Y: %d", pEvent->button.x, pEvent->button.y);
    }

    if(pEvent->type == SDL_KEYDOWN) {
        // Log("Key %d down", pEvent->key.keysym.scancode);
    }

    if(pEvent->type == SDL_KEYUP) {
        // Log("Key %d up", pEvent->key.keysym.scancode);
    }
}

void CApp::Update()
{
    mBackGround->Update();
}

void CApp::Render()
{
    SDL_RenderClear(mRenderer);

    mBackGround->Render(mRenderer);

    SDL_RenderPresent(mRenderer);
}

void CApp::CleanUp()
{
    if(mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }

    if(mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    SDL_Quit();
}
