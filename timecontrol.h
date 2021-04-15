#pragma once

#define minutes(M) (M * 1000 * 60)
#define seconds(S) (S * 1000)

#define msToMin(MS)         (MS / 1000 / 60);
#define msToSecOfMin(MS)    ((MS / 1000) % 60);

typedef struct Timecontrol_Conf {
    long time;
    long increment;
} Timecontrol_Conf;

typedef enum Timecontrol {
    BULLET,
    BLITZ,
    RAPID,
    CLASSIC,
    LONG
} Timecontrol;

Timecontrol_Conf get_conf(Timecontrol timectl);
