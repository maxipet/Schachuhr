#include "IOManager.h"

void IOManager::updateButtons() {
    btn_left->read();
    btn_right->read();
    btn_pause->read();
}

int IOManager::selectMenu(char name[], int values[], int start) {
    int cur = start;
    int length = sizeof(values) / sizeof(values[0]);
    display_left->displayStr(name);
    display_right->displayNumber(values[cur]);
    do {
        updateButtons();
        
        if(btn_left->wasReleased()) {
            cur -= 1;
            if(cur < 0) {
                cur = length - 1;
            }
            display_right->displayNumber(values[cur]);
        }
        if(btn_right->wasReleased()) {
            cur = (cur + 1) % length;
            display_right->displayNumber(values[cur]);
        }
    } while(!btn_pause->wasReleased());

    return values[cur];
}

int IOManager::rangeMenu(char name[], int min, int max, int step, int start) {
    int cur = start;
    if(cur > max)
        cur = max;
    if(cur < min)
        cur = min;
    
    display_left->displayStr(name);
    display_right->displayNumber(cur);
    do {
        updateButtons();

        if(btn_left->wasReleased()) {
            cur -= step;
            if(cur < min) {
                cur = min;
            }
            display_right->displayNumber(cur);
        }
        if(btn_right->wasReleased()) {
            cur += step;
            if(cur > max) {
                cur = max;
            }
            display_right->displayNumber(cur);
        }
    } while(!btn_pause->wasReleased());

    return cur;
}

int IOManager::keyMenu(char name[], char values[][5], int start) {
    int cur = start;
    int length = sizeof(values) / sizeof(values[0]);
    display_left->displayStr(name);
    display_right->displayStr(values[cur]);
    do {
        updateButtons();
        
        if(btn_left->wasReleased()) {
            cur -= 1;
            if(cur < 0) {
                cur = length - 1;
            }
            display_right->displayStr(values[cur]);
        }
        if(btn_right->wasReleased()) {
            cur = (cur + 1) % length;
            display_right->displayStr(values[cur]);
        }
    } while(!btn_pause->wasReleased());

    return cur;
}

// Singleton Stuff
IOManager* IOManager::instance = 0;

IOManager* IOManager::getInstance() {
    if (instance == 0) {
        instance = new IOManager();
    }
    return instance;
}

IOManager::IOManager() {
    // BUTTONS
    btn_left = new LedButton(PIN_BTN_LEFT, PIN_LED_LEFT);
    btn_right = new LedButton(PIN_BTN_RIGHT, PIN_LED_RIGHT);
    btn_pause = new LedButton(PIN_BTN_PAUSE, PIN_LED_PAUSE);

    btn_left->begin();
    btn_right->begin();
    btn_pause->begin();

    // DISPLAY
    display_left = new Display(PIN_CLK_LEFT, PIN_DIO_LEFT);
    display_right = new Display(PIN_CLK_RIGHT, PIN_DIO_RIGHT);

    display_left->init();
    display_left->set(BRIGHT_TYPICAL);
    display_right->init();
    display_right->set(BRIGHT_TYPICAL);

    // PIEZO
    piezo = new Piezo(PIN_PIEZO);
    piezo->begin();
}