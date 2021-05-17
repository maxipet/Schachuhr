#include "Game.h"

AbsoluteGame::AbsoluteGame() {
    
}

void AbsoluteGame::setup() {
    int list[] = {1,2,3,5,10,15,20,30,45,60,90,120,180};
    startTime = minToMs(io->selectMenu(
        "TIME", 
        list,
        5
    ));
}

void AbsoluteGame::update() {
    long deltaTime = millis() - lastTime;
    addPlayerTime(currentTurn, -deltaTime);
    lastTime = millis();
}

void AbsoluteGame::turn() {
    update();

    if(currentTurn == LEFT) {
        currentTurn = RIGHT;
    } else {
        currentTurn = LEFT;
    }
}

void AbsoluteGame::paused() {
    while(!io->btn_pause->wasReleased()) {
        io->updateButtons();

        if(io->btn_left->wasReleased()) {
            addPlayerTime(LEFT, startTime / 100L);
        }
        if(io->btn_right->wasReleased()) {
            addPlayerTime(RIGHT, startTime / 100L);
        }
    }
}