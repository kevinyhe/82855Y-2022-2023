// Copyright (c) 2022 STL Robotics Team 82855Y

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "main.h"
#include "pros/rtos.hpp"

// initialize our motors and globals here
pros::Motor right_front(10);
pros::Motor right_middle(2); // we don't know why this is reversed it's just like that
pros::Motor right_back(3);
pros::Motor left_front(4);
pros::Motor left_middle(5);
pros::Motor left_back(6);
pros::Motor roller(7);
pros::Motor expansion(1); //temporary, depends on where we attach expansion

// asign the motor groups for the left and right sides
// because we have already reversed the motors that will spin in the opposite direction
// we can make the same group spin in the same direction because there
// is no need to have one motor spin in the opposite direction as a neighboring motor
pros::Motor_Group left_motor_group({left_front, left_middle, left_back});
pros::Motor_Group right_motor_group({right_front, right_middle, right_back});

// initialize our controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

void initialize() { pros::lcd::initialize(); }

void disabled() {}

void competition_initialize() {}

// autonomous code will be triggered 
// in the first 15s of the round
void autonomous() {
    // as of 16/12/22, we have not yet added any functionality except
    // moving around, rollers and expansion so for now our autonomous
    // will be nothing but wreaking havoc on opposing autonomous code
    // by moving around and being a nuisance we can disrupt their code
    // if we're lucky, they won't be using sensors and will continue to 
    // move_relative and will be off by a few units and they start
    // with a severe disadvantage



    // TODO: poor programming, pls fix later
    left_front.move(127);
    left_middle.move(127);
    left_back.move(127);
    right_front.move(-127);
    right_middle.move(-127);
    right_back.move(-127);

    roller.move(-127);
    pros::delay(250);
    left_front.move(0);
    left_middle.move(0);
    left_back.move(0);
    right_front.move(0);
    right_middle.move(0);
    right_back.move(0);

    // pros::delay(425);
    roller.move(0);
    // while (true) {
    //     left_front.move(-127);
    //     left_middle.move(-127);
    //     left_back.move(-127);
    //     right_front.move(-127);
    //     right_middle.move(-127);
    //     right_back.move(-127);
    //     pros::delay(250);
    //     left_front.move(127);
    //     left_middle.move(127);
    //     left_back.move(127);
    //     right_front.move(127);
    //     right_middle.move(127);
    //     right_back.move(127);
    // }
}

// driver control
// if we fail we can all blame kerry
void opcontrol() {
    // initialze variables
    int drive_power, turn_power;
    bool roller_button, expansion_button, expansion_button_confirm, roller_button_opp;

    // it's bad practice to use an endless loop but 
    // we really have no choice here
    while (true) {
        // we initialize these variables outside of the loop
        // because type declaration inside will take up memory
        // and we want to use as little processing power as
        // possible
		turn_power = master.get_analog(ANALOG_LEFT_Y);
		drive_power = master.get_analog(ANALOG_RIGHT_X);
        roller_button_opp = master.get_digital(DIGITAL_R1);
        roller_button = master.get_digital(DIGITAL_L1);
        expansion_button = master.get_digital(DIGITAL_L2);
        expansion_button_confirm = master.get_digital(DIGITAL_R2);

        // assign expansion button to left 2 button
        // when endgame, expansion motor will launch string
        if (expansion_button && expansion_button_confirm) { expansion.move(-60); }
        else { expansion.move(0); }

        // assign roller button to left 1 button
        if (roller_button) { roller.move(127); }
        else { roller.move(0); }

        if (roller_button_opp) { roller.move(-127); }
        else { roller.move(0); }

        // // because readings of the analog channel range from -127 to 127
        // // scale the joystick values to be between -100 and 100
        // // so, we will use a percentage from -100% to 100%
        // analog_y *= 100 / 127;
        // analog_x *= 100 / 127;

        drive_power *= -0.6; // invert the x-axis
        turn_power *= -1; // invert the x-axis

        // // please refer to this, I don't know how to explain it
        // // https://home.kendra.com/mauser/Joystick.html
        // int vertical = (100 - abs(int(analog_x))) * (analog_y / 100) + analog_y;
        // int horizontal = (100 - abs(int(analog_y))) * (analog_x / 100) + analog_x;

        // int voltage_right = (((vertical - horizontal) / 2) / 100) * 127;
        // int voltage_left = (((vertical + horizontal) / 2) / 100) * 127;

        // // move the motor groups with the calculated voltage
		left_front.move(drive_power + turn_power);
		left_middle.move(drive_power + turn_power);
		left_back.move(drive_power + turn_power);
		right_front.move(drive_power - turn_power);
		right_middle.move(drive_power - turn_power);
		right_back.move(drive_power - turn_power);

        // add a little bit of delay so it doesn't overheat or whatever
        pros::delay(20);
    }
}
