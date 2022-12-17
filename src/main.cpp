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

// initialize our motors and globals here
pros::Motor left_front(10);
pros::Motor left_middle(2);
pros::Motor left_back(3);
pros::Motor right_front(4, true);
pros::Motor right_middle(5, true);
pros::Motor right_back(6);
pros::Motor roller(9);
pros::Motor expansion(11); //temporary, depends on where we attach expansion

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
    left_front.move_absolute(100, 100); // moves 100 units forward
    while (!((left_front.get_position() < 105) && (left_front.get_position() > 95))) {
        // continue running this loop as long as the motor is not within +-5 units of its goal
        pros::delay(2);
    }
    left_front.move_relative(100, 100); // also moves 100 units forward
    while (!((left_front.get_position() < 205) && (left_front.get_position() > 195))) {
        pros::delay(2);
    }
    // left_front.move_absolute(100, 200);
    // pros::delay(1000);
}

// driver control
// if we fail we can all blame kerry
void opcontrol() {
    // initialze variables
    int analog_y, analog_x;
    bool roller_button, expansion_button;

    // it's bad practice to use an endless loop but 
    // we really have no choice here
    while (true) {
        // we initialize these variables outside of the loop
        // because type declaration inside will take up memory
        // and we want to use as little processing power as
        // possible
        analog_y = master.get_analog(ANALOG_LEFT_Y);
        analog_x = master.get_analog(ANALOG_RIGHT_X);
        roller_button = master.get_digital(DIGITAL_L1);
        expansion_button = master.get_digital(DIGITAL_L2);

        // assign expansion button to left 2 button
        // when endgame, expansion motor will launch string
        if (expansion_button) { expansion.move(60); }
        else { expansion.move(0); }

        // assign roller button to left 1 button
        if (roller_button) { roller.move(127); }
        else { roller.move(0); }

        // because readings of the analog channel range from -127 to 127
        // scale the joystick values to be between -100 and 100
        // so, we will use a percentage from -100% to 100%
        analog_y *= 100 / 127;
        analog_x *= 100 / 127;

        analog_y *= -1; // invert the x-axis

        // please refer to this, I don't know how to explain it
        // https://home.kendra.com/mauser/Joystick.html
        int vertical = (100 - abs(int(analog_x))) * (analog_y / 100) + analog_y;
        int horizontal = (100 - abs(int(analog_y))) * (analog_x / 100) + analog_x;

        int voltage_right = (((vertical - horizontal) / 2) / 100) * 127;
        int voltage_left = (((vertical + horizontal) / 2) / 100) * 127;

        // move the motor groups with the calculated voltage
        left_motor_group.move(voltage_left);
        right_motor_group.move(voltage_right);

        // add a little bit of delay so it doesn't overheat or whatever
        pros::delay(20);
    }
}
