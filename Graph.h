#ifndef GRAPH_H
#define GRAPH_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "Board.h"


class Graph {

private:

    int *SCREEN_WIDTH;
    int *SCREEN_HEIGHT;


    SDL_Rect textDestRect;
    SDL_Rect startScreenDestRect;
    SDL_Rect xRect;
    SDL_Rect oRect;


    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
    SDL_Texture *gTexture = nullptr;
    SDL_Texture *drawTexture = nullptr;
    SDL_Texture *winTexture = nullptr;
    SDL_Texture *lostTexture = nullptr;
    SDL_Texture *startTexture = nullptr;
    TTF_Font *gFont = nullptr;

    SDL_Event events;







public:

    int mouseX;
    int mouseY;

    bool quit;
    bool clicked;

    bool startG;
    bool loopG;
    bool endG;

    char playerState;

    Graph();
    ~Graph();

    int getScreenWidth();
    int getScreenHeight();

    void loadTexture(std::string path);
    void loadTextTexture();

    void handleEvents();

    void renderStartScreen();
    void pickSide();

    void renderGameScreen(Board inputBoard);
    void renderWinScreen();
    void renderDrawScreen();
    void renderLostScreen();





};

#endif // GRAPH_H
