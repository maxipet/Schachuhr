#ifndef Timecontrol_H
#define Timecontrol_H

#define minutes(M) (M * 1000 * 60)
#define seconds(S) (S * 1000)

#define msToMin(MS)         (MS / 1000 / 60)
#define msToSec(MS)         (MS / 1000)
#define msToSecOfMin(MS)    ((MS / 1000) % 60)

typedef struct Timecontrol_Conf {
    long time;
    long increment;
} Timecontrol_Conf;

typedef enum Timecontrol {
    BULLET  = 0,
    BLITZ   = 1,
    RAPID   = 2,
    CLASSIC = 3,
    LONG    = 4,
    SIZE    = 5
} Timecontrol;

Timecontrol_Conf get_conf(Timecontrol timectl);

#endif