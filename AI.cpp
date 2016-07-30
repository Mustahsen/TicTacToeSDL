#include "AI.h"

AI::AI(Board _gameState){

    gameState = Board(_gameState);

    x = -1;
    y = -1;

}


AI::~AI(){

}

int AI::setNextMove(){

    if(gameState.getEmptySlotCount() == 9) return 0;

    char turn = this->findTurn();

    std::vector<winners> totalWinSituationPerMove;

    for (int i = 0; i < 9; i++){
        if(gameState.getSlotState(i/3, i%3) != 'e') continue;

        AI iterAI(gameState);

        totalWinSituationPerMove.push_back(iterAI.calculateNextMove(i));
        totalWinSituationPerMove.back().slot = i;

    }

    int maxDifference = 0;
    int returnValue = totalWinSituationPerMove.front().slot;
    for (auto i: totalWinSituationPerMove){
        if (turn == 'x'){
            int dif = i.x - i.o;
            if (dif > maxDifference){
                maxDifference = dif;
                returnValue = i.slot;
            }
        }
        if (turn == 'o'){
            int dif = i.o - i.x;
            if (dif > maxDifference){
                maxDifference = dif;
                returnValue = i.slot;
            }
        }
    }
    return returnValue;
}








winners AI::calculateNextMove(int vectorSlot){
    winners winnerCounts = {0, 0, 0};
    char turn = this->findTurn();

    if (turn == 'x') this->gameState.setSlotX(vectorSlot/3, vectorSlot%3);
    else if (turn == 'o') this->gameState.setSlotO(vectorSlot/3, vectorSlot%3);

    if(this->checkWinner() == 'x'){
        winnerCounts.x++;
        return winnerCounts;
    }
    else if(this->checkWinner() == 'o'){
        winnerCounts.o++;
        return winnerCounts;
    }

    else{
        if ( this->gameState.getEmptySlotCount() == 0 ){
            return winnerCounts;
        }


        for (int i = 0; i < 9; i++){
            if(gameState.getSlotState(i/3, i%3) == 'e'){
                AI iterAI(gameState);
                winners tempWinners = iterAI.calculateNextMove(i);
                winnerCounts.x += tempWinners.x;
                winnerCounts.o += tempWinners.o;

            }
        }
        return winnerCounts;

    }


}


/*char AI::calculateNextMove(int vectorSlot){
    winners winnerCounts = {0, 0, 0};
    char turn = this->findTurn();

    if (turn == 'x') this->gameState.setSlotX(vectorSlot/3, vectorSlot%3);
    else if (turn == 'o') this->gameState.setSlotO(vectorSlot/3, vectorSlot%3);

    std::cout << this->checkWinner() << std::endl;

    return this->checkWinner();

}*/

char AI::findTurn(){
    int xCount = 0, oCount = 0;
    for (int i = 0; i < 9; i ++){
        if (gameState.getSlotState(i/3, i%3) == 'x') xCount++;
        else oCount++;
    }
    return xCount > oCount ? 'o' : 'x';
}

char AI::checkWinner(){
    std::vector<coordinateStruct> x;
    std::vector<coordinateStruct> o;
    for (int i = 0; i < 9; i++){
        coordinateStruct tempStruct = {i/3, i%3};
        if (gameState.getSlotState(i/3, i%3) == 'x') x.push_back(tempStruct);
        else if (gameState.getSlotState(i/3, i%3) == 'o') o.push_back(tempStruct);
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

bool AI::colinear(coordinateStruct _x, coordinateStruct _y, coordinateStruct _z){
    return (_x.x * (_y.y - _z.y)) + (_y.x * (_z.y - _x.y)) + (_z.x * (_x.y - _y.y)) == 0;
}
