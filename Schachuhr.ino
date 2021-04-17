#include "Schachuhr.h"

// PINS
#define BTN_P0      1
#define BTN_P1      2
#define BTN_PAUSE   3

#define CLK_P0      4
#define DIO_P0      5
#define CLK_P1      6
#define DIO_P1      7

#define PIEZO       8


// SETTINGS
#define DEBOUNCE_TIME 20    // 20ms debouncing

#define TONE        261     // C

// STATE
Clockstate state;

// TIME
Timecontrol timectl;
Timecontrol_Conf timeconf;

int turn;
long playertime[2];
long lastTime;

// DISPLAY
TM1637 clock_p0(CLK_P0, DIO_P0);
TM1637 clock_p1(CLK_P1, DIO_P1);

// SCHACHUHR
void setup() {
    pinMode(BTN_P0, INPUT);
    pinMode(BTN_P1, INPUT);
    pinMode(BTN_PAUSE, INPUT);
    attachInterrupt(BTN_P0, int_btn_p0, LOW);
    attachInterrupt(BTN_P1, int_btn_p1, LOW);
    attachInterrupt(BTN_PAUSE, int_btn_pause, LOW);

    clock_p0.init();
    clock_p0.set(BRIGHT_TYPICAL);
    clock_p1.init();
    clock_p1.set(BRIGHT_TYPICAL);

    pinMode(PIEZO, OUTPUT);

    timectl = RAPID;
    displayTimeinfo();

    state = MENU;
}

void loop() {
    switch(state) {
        case MENU:      menu();     break;
        case READY:     ready();    break;
        case RUNNING:   running();  break;
        case PAUSED:    paused();   break;
        case EXPIRED:   expired();  break;
    }
}

// LIFECYCLE METHODS
void menu() {
    
}

void ready() {

}

void running() {
    updatePlayertime();

    if(playertime[0] <= 0 || playertime[1] <= 0) {
        state = EXPIRED;
        tone(PIEZO, TONE, seconds(1));
    }
}

void paused() {
    lastTime = millis();
}

void expired() {
    
}

reset() {
    state = MENU;
}

// INTERUPTS
void int_btn_p0() {
    static long lastInt = 0;
    if(millis() - lastInt > DEBOUNCE_TIME) {

        switch(state) {
            case MENU:
                prevTimectl();
                break;

            case READY:
                state       = RUNNING;
                turn        = 1;
                lastTime    = millis();
                break;

            case RUNNING:
                if(turn == 0)
                    switchTurn();
                break;

            case PAUSED:
                playertime[0] += seconds(timeconf.increment * 3);
                break;
            
            case EXPIRED:   reset(); break;
        }

        lastInt = millis();
    }
}

void int_btn_p1() {
    static long lastInt = 0;
    if(millis() - lastInt > DEBOUNCE_TIME) {

        switch(state) {
            case MENU:
                nextTimectl();
                break;

            case READY:
                state       = RUNNING;
                turn        = 0;
                lastTime    = millis();
                break;

            case RUNNING:
                if(turn == 1) {
                    switchTurn();
                }
                break;

            case PAUSED:
                playertime[1] += seconds(timeconf.increment * 3);
                break;

            case EXPIRED:   reset(); break;
        }
    
        lastInt = millis();
    }
}

void int_btn_pause() {
    static long lastInt = 0;
    if(millis() - lastInt > DEBOUNCE_TIME) {

        switch(state) {
            case MENU:
                state = READY;
                displayPlayertime();
                break;

            case READY:
                state = MENU; 
                displayTimeinfo();
                break;

            case RUNNING:   pause();    break;
            case PAUSED:    unpause();  break;
            case EXPIRED:   reset();    break;
        }

        lastInt = millis();
    }
}

// HELPERS
void pause() {
    updatePlayertime();
    state = PAUSED;
}

void unpause() {
    lastTime = millis();
    state = RUNNING;
}

void switchTurn() {
    updatePlayertime();
    playertime[turn] += increment;
    turn = (turn + 1) % 2; // toggles between 0 and 1
}

void updatePlayertime() {
    long deltaTime = lastTime - millis();
    playertime[turn] -= deltaTime;
    lastTime = millis();

    displayPlayertime();
}

void displayPlayertime() {
    // Clock p0
    clock_p0.point(1);
    clock_p0.display(0, msToMin(playertime[0]) / 10 % 10);
    clock_p0.display(1, msToMin(playertime[0]) % 10);
    clock_p0.display(2, msToSecOfMin(playertime[0]) / 10 % 10);
    clock_p0.display(3, msToSecOfMin(playertime[0]) % 10);
    // Clock p0
    clock_p1.point(1);
    clock_p1.display(0, msToMin(playertime[1]) / 10 % 10);
    clock_p1.display(1, msToMin(playertime[1]) % 10);
    clock_p1.display(2, msToSecOfMin(playertime[1]) / 10 % 10);
    clock_p1.display(3, msToSecOfMin(playertime[1]) % 10);
}

void displayTimeinfo() {
    // Clock p0
    clock_p0.point(0);
    clock_p0.display(0, msToMin(timeconf.time) / 1000 % 10);
    clock_p0.display(1, msToMin(timeconf.time) / 100 % 10);
    clock_p0.display(2, msToMin(timeconf.time) / 10 % 10);
    clock_p0.display(3, msToMin(timeconf.time) % 10);
    // Clock p0
    clock_p1.point(0);
    clock_p1.display(0, msToSec(timeconf.increment) / 1000 % 10);
    clock_p1.display(1, msToSec(timeconf.increment) / 100 % 10);
    clock_p1.display(2, msToSec(timeconf.increment) / 10 % 10);
    clock_p1.display(3, msToSec(timeconf.increment) % 10);
}

void nextTimectl() {
    timectl = (timectl + 1) % SIZE;
    timeconf = get_conf(timectl);
    playertime[0] = timeconf.time;
    playertime[1] = timeconf.time;
    displayTimeinfo();
}

void prevTimectl() {
    timectl = (timectl - 1) % SIZE;
    timeconf = get_conf(timectl);
    playertime[0] = timeconf.time;
    playertime[1] = timeconf.time;
    displayTimeinfo();
}