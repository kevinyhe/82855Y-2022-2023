#include "func/digital.h"
#include "config.h"
#include "main.h"

// mapping every digital button to a string just to make
// my life a tiny bit easier
std::map<std::string, pros::controller_digital_e_t> _m = {
    {"L1", DIGITAL_L1},	    {"L2", DIGITAL_L2},	      {"R1", DIGITAL_R1},
    {"R2", DIGITAL_R2},	    {"UP", DIGITAL_UP},	      {"DOWN", DIGITAL_DOWN},
    {"LEFT", DIGITAL_LEFT}, {"RIGHT", DIGITAL_RIGHT}, {"X", DIGITAL_X},
    {"B", DIGITAL_B},	    {"Y", DIGITAL_Y},	      {"A", DIGITAL_A},
};

/**
 * Code for all the digital buttons
 * i.e. rollers, flywheel, expansion
 */
void digital()
{
    b_roller = master.get_digital(_m["L1"]);
    b_flywheel = master.get_digital(_m["L2"]);
    b_expansion = master.get_digital(_m["A"]);
    b_expansion_c = master.get_digital(_m["LEFT"]);

    roller.move(b_roller ? -127 : 0);
    flywheel.move(b_flywheel ? -127 : 0);
};