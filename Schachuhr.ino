#include "Schachuhr.h"

Game* game;

IOManager* io;

void setup() {
    //Serial.begin(9600);

    io = IOManager::getInstance();
}

void loop() {
    char modes[5][5];
    modes[0] = "Fish";
    modes[1] = "Abso";
    modes[2] = "Gilo";
    modes[3] = "Hour";
    modes[4] = "Bron";

    int mode = io->keyMenu(
        "MODE",
        modes
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
