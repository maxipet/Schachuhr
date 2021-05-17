#include "Game.h"

FischerGame::FischerGame() {

}

void FischerGame::setup() {
    AbsoluteGame::setup();

    int list[] = {0,1,2,3,5,10,15,30,60,90,120};
    increment = secToMs(io->selectMenu(
        "Incr",
        list,
        4
    ));
}

void FischerGame::turn() {
    playerTimes[currentTurn] += increment;

    AbsoluteGame::turn();
}