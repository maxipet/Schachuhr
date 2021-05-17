#include "Game.h"

Game::Game() {
    io = IOManager::getInstance();
};

void Game::run() {
    do {
        setup();
    } while(!ready());

    running();
    expired();
};

bool Game::ready() {
    playerTimes[LEFT] = startTime;
    playerTimes[RIGHT] = startTime;

    displayPlayertime();
    while(true) {
        io->updateButtons();

        if(io->btn_left->wasReleased()) {
            currentTurn = RIGHT;
            lastTime = millis();
            return true;
        }
        else if(io->btn_right->wasReleased()) {
            currentTurn = LEFT;
            lastTime = millis();
            return true;
        }
        else if(io->btn_pause->wasReleased()) {
            return false;
        }
    }
};

void Game::running() {
    do {
        update();
        io->updateButtons();

        if(io->btn_left->wasReleased()) {
            if(currentTurn == LEFT) turn();
        }
        else if(io->btn_right->wasReleased()) {
            if(currentTurn == RIGHT) turn();
        }
        else if(io->btn_pause->wasReleased()) {
            paused();
        }
    } while(playerTimes[LEFT] <= 0 || playerTimes[RIGHT] <= 0);
};

void Game::expired() {
    io->piezo->play(261, 1000);

    while(!io->btn_left->wasReleased() 
        && !io->btn_right->wasReleased() 
        && !io->btn_pause->wasReleased())
    { 
        io->updateButtons();
    }
}

///////////////////////////////////////
//              HELPER               //
///////////////////////////////////////
void Game::displayPlayertime() {
    io->display_left->displayTime(
        msToMin(playerTimes[LEFT]), 
        msToSecOfMin(playerTimes[LEFT]));

    io->display_right->displayTime(
        msToMin(playerTimes[RIGHT]), 
        msToSecOfMin(playerTimes[RIGHT]));
}

void Game::addPlayerTime(Player p, long t) {
    playerTimes[p] += t;
    displayPlayertime();
}