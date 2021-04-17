#pragma once

#include "libs/Grove_4Digital_Display/TM1637.h"
#include "libs/JC_Button/src/JC_Button.h"

#include "timecontrol.h"

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

void switchTurn();

void updatePlayertime();
void displayPlayertime();
void displayTimeinfo();

void nextTimectl();
void prevTimectl();