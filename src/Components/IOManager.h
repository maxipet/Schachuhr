#ifndef IOManager_H
#define IOManager_H

#include "Display.h"
#include "LedButton.h"
#include "Piezo.h"

#define PIN_BTN_LEFT    2
#define PIN_LED_LEFT    3
#define PIN_BTN_RIGHT   4
#define PIN_LED_RIGHT   5
#define PIN_BTN_PAUSE   6
#define PIN_LED_PAUSE   7

#define PIN_CLK_LEFT    10
#define PIN_DIO_LEFT    11
#define PIN_CLK_RIGHT   12
#define PIN_DIO_RIGHT   13

#define PIN_PIEZO       9

class IOManager {
    public:
        LedButton *btn_left, *btn_right, *btn_pause;
        Display *display_left, *display_right;
        Piezo *piezo;

    public:
        void updateButtons();

        int selectMenu(char name[], int values[], int start = 0);
        int rangeMenu(char name[], int min, int max, int start, int step = 1);
        int keyMenu(char name[], char values[][5], int start = 0);

        void(* reset) (void) = 0;

    // Singleton Stuff
    private:
        static IOManager* instance;
        IOManager();
    public:
        static IOManager* getInstance();
};

#endif