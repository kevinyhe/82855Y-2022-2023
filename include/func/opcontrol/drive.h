#ifndef _DRIVE_H
#define _DRIVE_H

#include "main.h"

extern float turn_power_multiplier;
extern double drive_power;
extern double turn_power;
extern double voltage_left;
extern double voltage_right;

std::pair<int, int> motor_voltage(float i, float j);
void drive();

#endif /* _DRIVE_H */
