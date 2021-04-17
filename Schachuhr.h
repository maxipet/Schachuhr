#pragma once

#include <TM1637.h>

#include "timecontrol.h"

typedef enum clockstate {
    MENU,
    READY,
    RUNNING,
    PAUSED,
    EXPIRED
} Clockstate;

void pause();
void unpause();

void switchTurn();

void updatePlayertime();
void displayPlayertime();
void displayTimeinfo();

void nextTimectl();
void prevTimectl();