#include "main.h"
#include "func/drive.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(1, true);
pros::Motor left_middle(2, true);
pros::Motor left_back(3, true);

pros::Motor right_front(4);
pros::Motor right_middle(5);
pros::Motor right_back(6);

pros::Motor_Group left_motor_group({left_front, left_middle, left_back});
pros::Motor_Group right_motor_group({right_front, right_middle, right_back});

pros::Motor roller(11);

pros::Motor flywheel(10);
