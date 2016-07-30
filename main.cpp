#include "Board.h"
#include "AI.h"
#include "Graph.h"

#include <Windows.h>


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
                int posX = -1, posY = -1;
                if (screen.mouseX < (screen.getScreenWidth() - 10)/3) posX = 0;
                if (screen.mouseX > (((screen.getScreenWidth()- 10)/3) + 4) && screen.mouseX < (((screen.getScreenWidth() - 10)/3*2)+4)) posX = 1;
                if (screen.mouseX > (screen.getScreenWidth() - 10)/3*2) posX = 2;
                if (screen.mouseY < (screen.getScreenHeight() - 10)/3) posY = 0;
                if (screen.mouseY > (((screen.getScreenHeight() - 10)/3) + 4) && screen.mouseY < (((screen.getScreenHeight() - 10)/3*2)+4)) posY = 1;
                if (screen.mouseY > (screen.getScreenHeight() - 10)/3*2) posY = 2;
                if (posX != -1 && posY != -1 && gameBoard.getSlotState(posX, posY) == 'e'){
                    if (playerSide == 'x') gameBoard.setSlotX(posX, posY);
                    if (playerSide == 'o') gameBoard.setSlotO(posX, posY);
                    playerTurn = !playerTurn;
                    aiTurn = !aiTurn;
                    screen.clicked = false;
                }
            }
            if (gameBoard.checkWinner() == playerSide){
                playerTurn = false;
                aiTurn = false;
                screen.startG = false;
                screen.loopG = false;
                screen.endG = true;
                screen.renderGameScreen(gameBoard);
            }
            if (!playerTurn && aiTurn){
                AI ai(gameBoard);
                if (playerSide == 'x') gameBoard.setSlotO(ai.setNextMove() / 3, ai.setNextMove() % 3);
                if (playerSide == 'o') gameBoard.setSlotX(ai.setNextMove() / 3, ai.setNextMove() % 3);
                playerTurn = !playerTurn;
                aiTurn = !aiTurn;
            }
            char aiSide = 'x';
            if (playerSide == 'x') aiSide = 'o';
            if (gameBoard.checkWinner() == aiSide){
                playerTurn = false;
                aiTurn = false;
                screen.startG = false;
                screen.loopG = false;
                screen.endG = true;
                screen.renderGameScreen(gameBoard);
            }
            if (gameBoard.getEmptySlotCount() == 0 && gameBoard.checkWinner() == 'e'){
                playerTurn = false;
                aiTurn = false;
                screen.startG = false;
                screen.loopG = false;
                screen.endG = true;
                screen.renderGameScreen(gameBoard);
            }
            screen.renderGameScreen(gameBoard);
        }
        if (screen.endG){
            if(gameBoard.checkWinner() == 'e') screen.renderDrawScreen();
            else if(gameBoard.checkWinner() == playerSide) screen.renderWinScreen();
            else screen.renderLostScreen();

            if (screen.clicked){
                gameBoard.emptyAll();
                screen.startG = true;
                screen.loopG = false;
                screen.endG = false;
                screen.clicked = false;
            }
        }


    }

    return 0;

}
