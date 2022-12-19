// Copyright (c) 2022 STL Robotics Team 82855Y

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

#include "main.h"

// initialize our motors and globals here
pros::Motor left_front(4, true);
pros::Motor left_middle(5, true);
pros::Motor left_back(6, true);
pros::Motor right_front(10);
pros::Motor
    right_middle(2);
pros::Motor right_back(3);
pros::Motor roller(7);
pros::Motor expansion(1); // temporary, depends on where we attach expansion

// asign the motor groups for the left and right sides
// because we have already reversed the motors that will spin in the opposite
// direction we can make the same group spin in the same direction because there
// is no need to have one motor spin in the opposite direction as a neighboring
// motor
pros::Motor_Group left_motor_group({left_front, left_middle, left_back});
pros::Motor_Group right_motor_group({right_front, right_middle, right_back});

// initialize our controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

void initialize() { pros::lcd::initialize(); }

void disabled() {}

void competition_initialize() {}

// autonomous code will be triggered
// in the first 15s of the round
void autonomous()
{
    // as of 16/12/22, we have not yet added any functionality
    // except moving around, rollers and expansion so for now
    // our autonomous will be nothing but wreaking havoc on
    // opposing autonomous code by moving around and being a
    // nuisance we can disrupt their code if we're lucky, they
    // won't be using sensors and will continue to move_relative
    // and will be off by a few units and they start with a
    // severe disadvantage

    left_motor_group.move(-127); // move backwards
    right_motor_group.move(-127);
    roller.move(-127);

    pros::delay(250);
    left_motor_group.move(0);
    right_motor_group.move(0);
    roller.move(0);
}

/**
i: drive power
j: turn power
*/
std::tuple<int, int> motor_voltage(float i, float j)
{
    // because readings of the analog channel range from -127 to
    // 127 scale the joystick values to be between -100 and 100
    // so, we will use a percentage from -100% to 100%
    // first we cast the int to a float, then divide by 127
    // and multiply by 100 to get a percentage of full power
    float Y = (static_cast<float>(i) / 127.0) * 100;
    float X = (static_cast<float>(j) / 127.0) * 100;

    // please refer to this, I don't know how to explain it
    // https://home.kendra.com/mauser/Joystick.html
    int V = (100 - abs(int(X))) * (Y / 100) + Y;
    int W = (100 - abs(int(Y))) * (X / 100) + X;

    float R = static_cast<float>(((V - W) / 2.0)) / 100 * 127;
    float L = static_cast<float>(((V - W) / 2.0)) / 100 * 127;

    // return a tuple of the left and right motor voltages
    // also cast the floats to int16 because it doesn't accept
    // floating point numbers
    return std::make_tuple(static_cast<int16_t>(L), static_cast<int16_t>(R));
}

// driver control
// if we fail we can all blame kerry
void opcontrol()
{
    // initialze variables
    int drive_power, turn_power, voltage_left, voltage_right;
    float analog_x, analog_y;
    bool roller_button, expansion_button, expansion_button_confirm,
	roller_button_opp;

    // it's bad practice to use an endless loop but
    // we really have no choice here
    while (true)
	{
	    // we initialize these variables outside
	    // of the loop because type declaration
	    // inside will take up memory and we
	    // want to use as little processing
	    // power as possible

	    drive_power = master.get_analog(ANALOG_LEFT_Y);
	    turn_power = master.get_analog(ANALOG_RIGHT_X);
	    roller_button = master.get_digital(DIGITAL_L1);
	    expansion_button = master.get_digital(DIGITAL_L2);
	    expansion_button_confirm = master.get_digital(DIGITAL_R2);

	    roller.move((expansion_button && expansion_button_confirm) ? -60
								       : 0);
	    roller.move(roller_button ? 127 : 0);

	    std::tie(voltage_left, voltage_right) =
		motor_voltage(drive_power, turn_power);

	    // move the motor groups with the
	    // calculated voltage
	    left_motor_group.move(voltage_left);
	    right_motor_group.move(voltage_right);

	    // log
	    pros::lcd::print(1, "analog_x: %d", drive_power);
	    pros::lcd::print(2, "analog_y: %d", turn_power);
	    pros::lcd::print(3, "voltage_left: %d", voltage_left);
	    pros::lcd::print(4, "voltage_right: %d", voltage_right);

	    // add a little bit of delay so it
	    // doesn't overheat or whatever
	    pros::delay(20);
	}
}
