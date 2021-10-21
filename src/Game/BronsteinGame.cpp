#include "Game.h"

BronsteinGame::BronsteinGame() {
    currentDelay = 0L;
}

void BronsteinGame::setup() {
    AbsoluteGame::setup();

    int list[] = {1,2,3,5,10,15,30,60,90,120};
    delay = secToMs(io->selectMenu(
        "dely",
        list,
        3
    ));
}

void BronsteinGame::update() {
    long deltaTime = millis() - lastTime;

    if(currentDelay <= delay) {
        currentDelay += deltaTime;
    } else {
        addPlayerTime(currentTurn, -deltaTime);
    }

    lastTime = millis();
}

void BronsteinGame::turn() {
    currentDelay = 0L;
    AbsoluteGame::turn();
}