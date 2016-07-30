#include "Board.h"

Board::Board(){
    for (int i = 0; i < 9; i++){
        state.push_back('e');
    }
}

Board::Board(Board &srcBoard){
    for (int i = 0; i < 9; i++){
        state.push_back(srcBoard.getSlotState(i/3, i%3));
    }
}

Board::~Board(){

}

char Board::getSlotState(int x, int y){
    return state[(3*x) + y];
}

std::vector<char> Board::getAllSlotStates(){
    return state;
}

int Board::getEmptySlotCount(){
    int counter = 0;
    for (int i = 0; i < 9; i++){
        if (state[i] == 'e') counter++;
    }
    return counter;
}

void Board::setSlotX(int x, int y){
    state[(3*x) + y] = 'x';
}

void Board::setSlotO(int x, int y){
    state[(3*x) + y] = 'o';
}

void Board::setSlotE(int x, int y){
    state[(3*x) + y] = 'e';
}

void Board::emptyAll(){
    for (int i = 0; i < 9; i++){
        state[i] = 'e';
    }
}

char Board::checkWinner(){
    std::vector<coordinateStruct> x;
    std::vector<coordinateStruct> o;
    for (int i = 0; i < 9; i++){
        coordinateStruct tempStruct = {i/3, i%3};
        if (this->getSlotState(i/3, i%3) == 'x') x.push_back(tempStruct);
        else if (this->getSlotState(i/3, i%3) == 'o') o.push_back(tempStruct);
    }
    if (x.size() > 2){
        for (int i = 0; i < x.size(); i++){
            for (int j = i + 1; j < x.size(); j++){
                for (int k = j + 1; k < x.size(); k++){
                    if (colinear(x [i], x[j], x[k])) return 'x';
                }
            }
        }
    }
    if (o.size() > 2){
        for (int i = 0; i < o.size(); i++){
            for (int j = i + 1; j < o.size(); j++){
                for (int k = j + 1; k < o.size(); k++){
                    if (colinear (o[i], o[j], o[k])) return 'o';
                }
            }
        }
    }
    return 'e';
}

bool Board::colinear(coordinateStruct _x, coordinateStruct _y, coordinateStruct _z){
    return (_x.x * (_y.y - _z.y)) + (_y.x * (_z.y - _x.y)) + (_z.x * (_x.y - _y.y)) == 0;
}
