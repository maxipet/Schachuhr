#include "Game.h"

AbsoluteGame::AbsoluteGame() {
    
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

        // Exit current Game
        if(io->btn_pause->pressedFor(3000)) {
            io->reset();
        }
        // add Time for Player Left
        if(io->btn_left->wasReleased()) {
            addPlayerTime(LEFT, startTime / 100L);
        }
        // add Time for Player Right
        if(io->btn_right->wasReleased()) {
            addPlayerTime(RIGHT, startTime / 100L);
        }
    }
}