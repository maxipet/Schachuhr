#ifndef Test_H
#define Test_H

#include "../Components/IOManager.h"

class Test {

    public:
        Test();

        void MenuTest();
        void ButtonTest();
        void DisplayTest();

    protected:
        IOManager* io;

};

#endif