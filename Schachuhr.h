#ifndef Schachuhr_H
#define Schachuhr_H

#include "src/Grove_4Digital_Display/TM1637.h"
#include "src/JC_Button/src/JC_Button.h"

#include "Timecontrol.h"

typedef enum clockstate {
    MENU,
    READY,
    RUNNING,
    PAUSED,
    EXPIRED
} Clockstate;

void updateButtons();

void pause();
void unpause();
void reset();

void switchTurn();

void updatePlayertime();
void displayPlayertime();
void displayTimeinfo();

void nextTimectl();
void prevTimectl();

#endif