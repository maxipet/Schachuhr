#ifdef __cplusplus
extern "C" {
#endif

#ifndef Timecontrol_H
#define Timecontrol_H

#define minutes(M) (M * 1000L * 60L)
#define seconds(S) (S * 1000L)

#define msToMin(MS)         (MS / 1000L / 60L)
#define msToSec(MS)         (MS / 1000L)
#define msToSecOfMin(MS)    ((MS / 1000L) % 60L)

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

#ifdef __cplusplus
}
#endif