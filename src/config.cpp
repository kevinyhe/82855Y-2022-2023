#include "config.h"
#include "func/auton/compute.h"
#include "main.h"

units::position location(units::coord(0, 0), units::angle());

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(PORT_LEFT_FRONT, true);
pros::Motor left_middle(PORT_LEFT_MIDDLE, true);
pros::Motor left_back(PORT_LEFT_BACK, true);

pros::Motor right_front(PORT_RIGHT_FRONT);
pros::Motor right_middle(PORT_RIGHT_MIDDLE);
pros::Motor right_back(PORT_RIGHT_BACK);

pros::Motor_Group left_motor_group({left_front, left_middle, left_back});
pros::Motor_Group right_motor_group({right_front, right_middle,
                                            right_back});

pros::Motor roller(PORT_ROLLER);

pros::Motor flywheel(PORT_FLYWHEEL);

sensors::ADI_tracking_wheel* left_encoder =
    new sensors::ADI_tracking_wheel(LEFT_TRACKING_PORT, true, WHEEL_DIAMETER);
sensors::ADI_tracking_wheel* right_encoder =
    new sensors::ADI_tracking_wheel(RIGHT_TRACKING_PORT, true, WHEEL_DIAMETER);
sensors::ADI_tracking_wheel* back_encoder =
    new sensors::ADI_tracking_wheel(BACK_TRACKING_PORT, false, WHEEL_DIAMETER);