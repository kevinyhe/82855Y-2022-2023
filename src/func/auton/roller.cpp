#include "config.h"
#include "main.h"

// TODO: rework this because it's garbage
/**
 * Move the roller during the autonomous period
 * This function will move the roller during the autonomous period
 */
void move_roller_autonomous()
{
    left_motor_group.move(127); // move backwards
    right_motor_group.move(127);
    roller.move(127); // start the roller

    pros::delay(300);	      // delay for 250
    left_motor_group.move(0); // stop the motors
    right_motor_group.move(0);
    roller.move(0);
}
