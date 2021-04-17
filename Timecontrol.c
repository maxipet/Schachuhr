#include "Timecontrol.h"

Timecontrol_Conf tc_bullet  = { minutes(3),  seconds(1) };
Timecontrol_Conf tc_blitz   = { minutes(5),  seconds(3) };
Timecontrol_Conf tc_rapid   = { minutes(10), seconds(5) };
Timecontrol_Conf tc_classic = { minutes(20), seconds(15) };
Timecontrol_Conf tc_long    = { minutes(60), seconds(30) };

Timecontrol_Conf get_conf(Timecontrol timectl) {
    switch(timectl) {
        case BULLET:    return tc_bullet;
        case BLITZ:     return tc_blitz;
        case RAPID:     return tc_rapid;
        case CLASSIC:   return tc_classic;
        case LONG:      return tc_long;
    }
}
