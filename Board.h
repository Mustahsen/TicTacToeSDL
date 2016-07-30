#ifndef BOARD_H
#define BOARD_H


#include <vector>

struct coordinateStruct{
    int x;
    int y;
};

class Board {

private:

    std::vector<char> state;

public:

    Board();
    Board(Board &srcBoard);
    ~Board();

    char getSlotState(int x, int y);

    std::vector<char> getAllSlotStates();
    int getEmptySlotCount();

    void setSlotX(int x, int y);
    void setSlotO(int x, int y);
    void setSlotE(int x, int y);

    void emptyAll();

    char checkWinner();
    bool colinear(coordinateStruct _x, coordinateStruct _y, coordinateStruct _z);

};



#endif // BOARD_H
