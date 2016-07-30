#include "Board.h"
#include "AI.h"
#include "Graph.h"


int main(int argc, char *argv[]){


    Graph screen;
    screen.loadTexture("tic.png");
    screen.loadTextTexture();

    Board gameBoard;

    char playerSide;
    bool playerTurn = false;
    bool aiTurn = false;

    while(!screen.quit){ // main game loop
        screen.handleEvents();

        if(screen.startG){
            screen.renderStartScreen();
            if (screen.clicked){
                screen.pickSide();
                playerSide = screen.playerState;
                if (playerSide == 'x'){
                    playerTurn = true;
                    aiTurn = false;
                }
                else{
                    aiTurn = true;
                    playerTurn = false;
                }
                screen.clicked = false;
            }
        }

        if(screen.loopG){
            if (screen.clicked && playerTurn && !aiTurn){

            }
            AI ai(gameBoard);
            std::cout << ai.setNextMove() << std::endl;
        }



    }

    return 0;

}
