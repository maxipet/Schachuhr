#include "Test.h"
#include <Arduino.h>

Test::Test() {
    io = IOManager::getInstance();
}

void Test::MenuTest() {

}

void Test::ButtonTest() {
    LedButton* btn = io->btn_left;

    btn->setLed(false);
    while(!btn->pressedFor(2000)) {
        btn->read();

        if(btn->wasReleased()) {
            btn->toggleLed();
        }
    }

    btn->setLed(true);
    delay(1000);
    btn->setLed(false);
    delay(1000);
    btn->setLed(true);
    delay(1000);
    btn->setLed(false);
    delay(1000);
    btn->setLed(true);
    delay(1000);
    btn->setLed(false);
    delay(1000);
}

void Test::DisplayTest() {
    Display* display = io->display_left;

    display->displayStr("TEST");
    delay(4000);
    display->displayTime(55L, 30L);
    delay(4000);
    display->displayTime(115L, 30L);
    delay(4000);
    display->displayNumber(1337);

}