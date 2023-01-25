#ifndef _DRIVE_H
#define _DRIVE_H

#include "config.h"
#include "main.h"


extern float turn_power_multiplier;
extern int drive_power;
extern int turn_power;
extern int voltage_left;
extern int voltage_right;

std::tuple<int, int> motor_voltage(float i, float j);
void drive();

#endif /* _DRIVE_H */
