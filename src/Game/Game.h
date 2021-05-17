#ifndef Game_H
#define Game_H

#define minToMs(M)  ((long) M * 1000L * 60L)
#define secToMs(S)  ((long) S * 1000L)

#define msToMin(MS)         ((long) MS / 1000L / 60L)
#define msToSec(MS)         ((long) MS / 1000L)
#define msToSecOfMin(MS)    (((long) MS / 1000L) % 60L)

#include "../Components/IOManager.h"

enum Player { LEFT = 0, RIGHT = 1 };

class Game {
    public:
        Game();
        void run();

    protected:
        virtual void setup() = 0;
        bool ready();
        void running();
        virtual void update() = 0;
        virtual void turn() = 0;
        virtual void paused() = 0;
        void expired();

    protected:
        long playerTimes[2];
        long lastTime;
        Player currentTurn;

    protected:
        IOManager* io;

    protected:
        void displayPlayertime();
        void addPlayerTime(Player p, long t);
};

class AbsoluteGame : public Game {
    public:
        AbsoluteGame();

    protected:
        virtual void setup();
        virtual void update();
        virtual void turn();
        virtual void paused();

    protected:
        long startTime;
};

class FischerGame : public AbsoluteGame {
    public:
        FischerGame();

    protected:
        virtual void setup();
        virtual void turn();

    protected:
        long increment;
};

class GuillotineGame : public FischerGame {
    public:
        GuillotineGame();

    protected:
        virtual void setup();
        virtual void turn();

    protected:
        long addonTime;
        int addonMove;
        int currentMoves[2];
};

class HourglassGame : public AbsoluteGame {
    public:
        HourglassGame();

    protected:
        virtual void update();
};

class BronsteinGame : public AbsoluteGame {
    public:
        BronsteinGame();

    protected:
        virtual void setup();
        virtual void update();
        virtual void turn();
    
    protected:
        long delay;
        long currentDelay;
};

#endif