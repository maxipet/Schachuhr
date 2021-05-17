#include "Game.h"

GuillotineGame::GuillotineGame() {
    currentMoves[0] = 0;
    currentMoves[1] = 0;
}

void GuillotineGame::setup() {
    FischerGame::setup();
    
    int list[] = {1,2,3,5,10,20,30,45,60};
    addonTime = minToMs(io->selectMenu(
        "AddO",
        list,
        6
    ));

    addonMove = io->rangeMenu("MOVE", 1, 80, 40);
}

void GuillotineGame::turn() {
    currentMoves[currentTurn] += 1;

    if(currentMoves[currentTurn] == addonMove) {
        playerTimes[currentTurn] += addonTime;
    }

    FischerGame::turn();
}