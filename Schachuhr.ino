#include "Schachuhr.h"

// PINS
#define PIN_BTN_P0      2
#define PIN_LED_P0      3
#define PIN_BTN_P1      4
#define PIN_LED_P1      5
#define PIN_BTN_PAUSE   6
#define PIN_LED_PAUSE   7

#define PIN_CLK_P0      10
#define PIN_DIO_P0      11
#define PIN_CLK_P1      12
#define PIN_DIO_P1      13

#define PIN_PIEZO       9

// BUTTONS
LedButton btn_p0(PIN_BTN_P0, PIN_LED_P0);
LedButton btn_p1(PIN_BTN_P1, PIN_LED_P1);
LedButton btn_pause(PIN_BTN_PAUSE, PIN_LED_PAUSE);

// DISPLAY
TM1637 clock_p0(PIN_CLK_P0, PIN_DIO_P0);
TM1637 clock_p1(PIN_CLK_P1, PIN_DIO_P1);

// SETTINGS
#define TONE 261     // C

// STATE
Clockstate state;

// TIME
Timecontrol timectl;
Timecontrol_Conf timeconf;

int turn;
long playertime[2];
long lastTime;

// SCHACHUHR
void setup() {
    Serial.begin(9600);
    
    btn_p0.begin();
    btn_p1.begin();
    btn_pause.begin();

    clock_p0.init();
    clock_p0.set(BRIGHT_TYPICAL);
    clock_p1.init();
    clock_p1.set(BRIGHT_TYPICAL);

    pinMode(PIN_PIEZO, OUTPUT);

    timectl = RAPID;
    timeconf = get_conf(timectl);
    displayTimeinfo();

    state = MENU;
}

void loop() {
    updateButtons();

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
    if(btn_p0.wasReleased()) {
        prevTimectl();
    }
    if(btn_p1.wasReleased()) {
        nextTimectl();
    }
    if(btn_pause.wasReleased()) {
        state = READY;
        displayPlayertime();
    }
}

void ready() {
    if(btn_p0.wasReleased()) {
        state       = RUNNING;
        turn        = 1;
        lastTime    = millis();
    }
    if(btn_p1.wasReleased()) {
        state       = RUNNING;
        turn        = 0;
        lastTime    = millis();
    }
    if(btn_pause.wasReleased()) {
        state = MENU; 
        displayTimeinfo();
    }
}

void running() {
    updatePlayertime();

    if(btn_p0.wasReleased()) {
        if(turn == 0) switchTurn();
    }
    if(btn_p1.wasReleased()) {
        if(turn == 1) switchTurn();
    }
    if(btn_pause.wasReleased()) {
        pause();
    }

    if(playertime[0] <= 0 || playertime[1] <= 0) {
        state = EXPIRED;
        tone(PIN_PIEZO, TONE, seconds(1));
    }
}

void paused() {
    if(btn_p0.wasReleased()) {
        playertime[0] += timeconf.increment * 3;
        displayPlayertime();
    }
    if(btn_p1.wasReleased()) {
        playertime[1] += timeconf.increment * 3;
        displayPlayertime();
    }
    if(btn_pause.wasReleased()) {
        unpause();
    }
}

void expired() {
    if(btn_p0.wasReleased()) {
        reset();
    }
    if(btn_p1.wasReleased()) {
        reset();
    }
    if(btn_pause.wasReleased()) {
        reset();
    }
}

void reset() {
    state = MENU;
    displayTimeinfo();
}

// HELPERS
void updateButtons() {
    btn_p0.read();
    btn_p1.read();
    btn_pause.read();
}

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
    playertime[turn] += timeconf.increment;
    turn = (turn + 1) % 2; // toggles between 0 and 1
}

void updatePlayertime() {
    long deltaTime = millis() - lastTime;
    playertime[turn] -= deltaTime;
    lastTime = millis();

    displayPlayertime();
}

void displayPlayertime() {
    // Clock p0
    clock_p0.point(POINT_ON);
    clock_p0.display(0, msToMin(playertime[0]) / 10 % 10);
    clock_p0.display(1, msToMin(playertime[0]) % 10);
    clock_p0.display(2, msToSecOfMin(playertime[0]) / 10 % 10);
    clock_p0.display(3, msToSecOfMin(playertime[0]) % 10);
    // Clock p0
    clock_p1.point(POINT_ON);
    clock_p1.display(0, msToMin(playertime[1]) / 10 % 10);
    clock_p1.display(1, msToMin(playertime[1]) % 10);
    clock_p1.display(2, msToSecOfMin(playertime[1]) / 10 % 10);
    clock_p1.display(3, msToSecOfMin(playertime[1]) % 10);
}

void displayTimeinfo() {
    // Clock p0
    clock_p0.point(POINT_OFF);
    clock_p0.display(0, msToMin(timeconf.time) / 1000 % 10);
    clock_p0.display(1, msToMin(timeconf.time) / 100 % 10);
    clock_p0.display(2, msToMin(timeconf.time) / 10 % 10);
    clock_p0.display(3, msToMin(timeconf.time) % 10);
    // Clock p0
    clock_p1.point(POINT_OFF);
    clock_p1.display(0, (msToSec(timeconf.increment) / 1000) % 10);
    clock_p1.display(1, (msToSec(timeconf.increment) / 100) % 10);
    clock_p1.display(2, (msToSec(timeconf.increment) / 10) % 10);
    clock_p1.display(3, msToSec(timeconf.increment) % 10);
}

void nextTimectl() {
    timectl = timectl + 1 % SIZE;
    timeconf = get_conf(timectl);
    playertime[0] = timeconf.time;
    playertime[1] = timeconf.time;
    displayTimeinfo();
}

void prevTimectl() {
    timectl = timectl - 1;
    if(timectl < 0) timectl = SIZE - 1;
    timeconf = get_conf(timectl);
    playertime[0] = timeconf.time;
    playertime[1] = timeconf.time;
    displayTimeinfo();
}
