#ifndef Display_H
#define Display_H

#include <Arduino.h>

#include "../Grove_4Digital_Display/TM1637.h"

class Display : public TM1637 {
    public:
        Display(uint8_t clk, uint8_t data)
            : TM1637(clk, data) {}
    
        void displayTime(long min, long sec) {
            TM1637::point(POINT_ON);
            TM1637::display(0, min / 10 % 10);
            TM1637::display(1, min % 10);
            TM1637::display(2, sec / 10 % 10);
            TM1637::display(3, sec % 10);
        }

        void displayNumber(int n) {
            TM1637::point(POINT_OFF);
            TM1637::display(0, n / 1000 % 10);
            TM1637::display(1, n / 100 % 10);
            TM1637::display(2, n / 10 % 10);
            TM1637::display(3, n % 10);
        }
};

#endif