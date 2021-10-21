#include "Test.h"

Test::Test() {
    io = IOManager::getInstance();
}

void Test::MenuTest() {

}

void Test::ButtonTest() {
    LedButton* btn = io.btn_left;

    btn->setLed(false);
    while(!btn->pressedFor(2000)) {
        btn->read();

        if(btn->wasReleased()) {
            btn->toggleLed();
        }
    }
}