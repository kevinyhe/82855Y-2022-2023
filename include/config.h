// Copyright (c) 2023 STL Robotics 82855Y

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "datatype.h"
#include "func/auton/PID.h"
#include "func/auton/odom.h"
#include "func/auton/roller.h"
#include "func/opcontrol/digital.h"
#include "func/opcontrol/drive.h"
#include "func/sensors/tracking.h"
#include "main.h"
#include "pros/adi.hpp"

#ifndef _CONFIG_H
#define _CONFIG_H

#define PI 3.14159265358979323846
#define WHEEL_DIAMETER 2.75
#define WHEEL_CIRCUMFERENCE (WHEEL_DIAMETER * PI)
#define TICKS_PER_REVOLUTION 360
#define TICKS_PER_INCH (TICKS_PER_REVOLUTION / WHEEL_CIRCUMFERENCE)

#define LEFT_ENCODER_DISTANCE 2
#define RIGHT_ENCODER_DISTANCE 2
#define BACK_ENCODER_DISTANCE 3

#define PORT_LEFT_FRONT 1
#define PORT_LEFT_MIDDLE 2
#define PORT_LEFT_BACK 3
#define PORT_RIGHT_FRONT 4
#define PORT_RIGHT_MIDDLE 5
#define PORT_RIGHT_BACK 6
#define PORT_ROLLER 11
#define PORT_FLYWHEEL 10
#define LEFT_TRACKING_PORT std::pair<int, int>(1, 2)
#define RIGHT_TRACKING_PORT std::pair<int, int>(3, 4)
#define BACK_TRACKING_PORT std::pair<int, int>(5, 6)

#define DRIVE_PID_P 0.0
#define DRIVE_PID_I 0.0
#define DRIVE_PID_D 0.0

#define TURN_PID_P 0.0
#define TURN_PID_I 0.0
#define TURN_PID_D 0.0

#define PID_MAX 200 

extern units::position location;

extern pros::Controller master;

extern pros::Motor left_front;
extern pros::Motor left_middle;
extern pros::Motor left_back;

extern pros::Motor right_front;
extern pros::Motor right_middle;
extern pros::Motor right_back;

extern pros::Motor_Group left_motor_group;
extern pros::Motor_Group right_motor_group;

extern pros::Motor roller;

extern pros::Motor flywheel;

extern sensors::ADI_tracking_wheel* left_encoder;
extern sensors::ADI_tracking_wheel* right_encoder;
extern sensors::ADI_tracking_wheel* back_encoder;

#endif /* _CONFIG_H */