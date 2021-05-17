#include "Game.h"

HourglassGame::HourglassGame() {

};

void HourglassGame::update() {
    long deltaTime = millis() - lastTime;
    
    if(currentTurn == LEFT) {
        addPlayerTime(LEFT, -deltaTime);
        addPlayerTime(RIGHT, deltaTime);
    } else {
        addPlayerTime(LEFT, deltaTime);
        addPlayerTime(RIGHT, -deltaTime);
    }

    lastTime = millis();
}