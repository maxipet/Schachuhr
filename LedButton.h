#ifndef Button_H
#define Button_H

#include <Arduino.h>

#include "src/JC_Button/src/JC_Button.h"

class LedButton : Button
{
    public:

        LedButton(uint8_t pin, uint8_t pinLed, bool initialState=false, uint32_t dbTime=25, uint8_t puEnable=true, uint8_t invert=true)
            : Button(pin, dbTime, puEnable, invert), m_pinLed(pinLed), m_ledState(initialState) {}

        void begin() {
            Button::begin();
            pinMode(m_pinLed, OUTPUT);
        }

        bool read()
        {
            // maybe update for blinkin LED here!
            return Button::read();
        }

        bool toggleLed() {
            if(m_ledState) {
                m_ledState = false;
                digitalWrite(m_pinLed, LOW);
            } else {
                m_ledState = true;
                digitalWrite(m_pinLed, HIGH);
            }
            return m_ledState;
        }


        void setLed(bool newState) {
            if(newState != m_ledState)
                toggleLed();
        }

    private:
        uint8_t m_pinLed;   // arduino pin for Led
        bool m_ledState;    // current state of Led
}

#endif