#ifndef AI_H
#define AI_H

#include <iostream>


#include "Board.h"


struct winners{
    int x;
    int o;
    int slot;
};

class AI{

private:

    Board gameState;

    int x;
    int y;

    winners calculateNextMove(int vectorSlot);
    char findTurn();
    char checkWinner();
    bool colinear(coordinateStruct _x, coordinateStruct _y, coordinateStruct _z);

public:

    AI(Board _gameState);
    ~AI();

    int setNextMove();

    int getX();
    int getY();

};

#endif // AI_H
