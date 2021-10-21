#include "Schachuhr.h"

Game* game;

IOManager* io;

void setup() {
    //Serial.begin(9600);

    io = IOManager::getInstance();
}

void loop() {
    int mode = io->keyMenu(
        "MODE",
        {"Fish","Abs","Gilo","Hour","Bron"}
    );

    switch(mode) {
        case 0: game = new FischerGame();
                break;
        case 1: game = new AbsoluteGame();
                break;
        case 2: game = new GuillotineGame();
                break;
        case 3: game = new HourglassGame();
                break;
        case 4: game = new BronsteinGame();
                break;
    }

    game->run();
}