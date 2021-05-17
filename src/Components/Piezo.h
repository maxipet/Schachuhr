#ifndef Piezo_H
#define Piezo_H

#include <Arduino.h>

class Piezo {
    public:
        Piezo(int p): pin(p) {}

        void begin() {
            pinMode(pin, OUTPUT);
        }

        void play(int frequency, int duration) {
            tone(pin, frequency, duration);
        }

    private:
        int pin;
};

#endif