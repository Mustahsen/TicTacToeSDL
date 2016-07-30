#include "Graph.h"

Graph::Graph(){

    SCREEN_WIDTH = new int(460);
    SCREEN_HEIGHT = new int(460);

    xRect = {307, 0, 293, 270};
    oRect = {0, 0, 250, 270};
    textDestRect = {*SCREEN_WIDTH/3, *SCREEN_HEIGHT/3, *SCREEN_WIDTH/3, *SCREEN_HEIGHT/3};

    startG = true;
    loopG = false;
    endG = false;

    quit = false;
    clicked = false;
    playerState = 'e';


    if (SDL_CreateWindowAndRenderer(*SCREEN_WIDTH, *SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &gWindow, &gRenderer) != 0){
        printf( "Window or Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    }
    else {
        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
            printf( "SDL Image PNG Library could not be initialized! SDL_Image Error: %s\n", IMG_GetError() );
        }
        if( TTF_Init() == -1 ){
            printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        else{
            gFont = TTF_OpenFont( "arial.ttf", 64 );
        }
    }
}

Graph::~Graph(){

    SDL_DestroyTexture( gTexture );
    SDL_DestroyTexture( winTexture );
    SDL_DestroyTexture( drawTexture );
    SDL_DestroyTexture( lostTexture );
    gTexture = nullptr;
    winTexture = nullptr;
    drawTexture = nullptr;
    lostTexture = nullptr;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    gRenderer = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();

    delete SCREEN_HEIGHT;
    delete SCREEN_WIDTH;
}

void Graph::loadTexture(std::string path){

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (!loadedSurface){
        printf( "Surface could not be created from the input image. SDL_Image Error: %s\n", IMG_GetError() );
    }
    else{
        gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    }
}


void Graph::loadTextTexture(){

    std::string tempString = "Choose your side:";

    SDL_Surface *loadedSurface = TTF_RenderText_Solid( gFont, tempString.c_str(), { 0, 0, 0 });

    if (!loadedSurface){
        printf( "Surface could not be created from the input image. SDL_Image Error: %s\n", IMG_GetError() );
    }
    else{
        startTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    }

    tempString = "You Win!";

    loadedSurface = TTF_RenderText_Solid( gFont, tempString.c_str(), { 0, 0, 0 });

    if (!loadedSurface){
        printf( "Surface could not be created from the input image. SDL_Image Error: %s\n", IMG_GetError() );
    }
    else{
        winTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    }

    tempString = "You Lost!";

    loadedSurface = TTF_RenderText_Solid( gFont, tempString.c_str(), { 0, 0, 0 });

    if (!loadedSurface){
        printf( "Surface could not be created from the input image. SDL_Image Error: %s\n", IMG_GetError() );
    }
    else{
        lostTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    }

    tempString = "Draw!";

    loadedSurface = TTF_RenderText_Solid( gFont, tempString.c_str(), { 0, 0, 0 });

    if (!loadedSurface){
        printf( "Surface could not be created from the input image. SDL_Image Error: %s\n", IMG_GetError() );
    }
    else{
        drawTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    }
}

void Graph::handleEvents(){
    while(SDL_PollEvent(&events) != 0){
        if(events.type == SDL_QUIT)quit = true;
        if(events.type == SDL_MOUSEMOTION)SDL_GetMouseState(&mouseX,&mouseY);
        if(events.type == SDL_MOUSEBUTTONDOWN)clicked = true;
    }
}

void Graph::renderStartScreen(){

    SDL_SetRenderDrawColor(gRenderer, 0xCC, 0xCC, 0xCC, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_GetWindowSize(gWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
    startScreenDestRect = {*SCREEN_WIDTH/10, *SCREEN_HEIGHT/10, *SCREEN_WIDTH/10*8, *SCREEN_HEIGHT/10*4};
    SDL_RenderCopy(gRenderer, startTexture, NULL, &startScreenDestRect);
    SDL_Rect xDestRect = {*SCREEN_WIDTH/10, *SCREEN_HEIGHT/10*5, *SCREEN_WIDTH/10*4, *SCREEN_HEIGHT/10*4};
    SDL_Rect oDestRect = {*SCREEN_WIDTH/10*5, *SCREEN_HEIGHT/10*5, *SCREEN_WIDTH/10*4, *SCREEN_HEIGHT/10*4};
    SDL_RenderCopy(gRenderer, gTexture, &xRect, &xDestRect);
    SDL_RenderCopy(gRenderer, gTexture, &oRect, &oDestRect);
    SDL_RenderPresent(gRenderer);

}

void Graph::pickSide(){
    if((mouseX < *SCREEN_WIDTH/10*5) && (mouseX >= *SCREEN_WIDTH/10) && (mouseY >= *SCREEN_HEIGHT/10*5) && (mouseY < *SCREEN_WIDTH/10*9)) playerState = 'x';
    else if((mouseX >= *SCREEN_WIDTH/10*5) && (mouseX < *SCREEN_WIDTH/10*9) && (mouseY >= *SCREEN_HEIGHT/10*5) && (mouseY < *SCREEN_WIDTH/10*9)) playerState = 'o';
    if (playerState == 'x' || playerState == 'o'){
        startG = false;
        loopG = true;
        endG = false;
    }
}

void Graph::renderGameScreen(){

}



