/**
Copyright (c) 2022 STL Robotics Team 82855Y Yellow Jackets

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "main.h"

/**
 * Initialize our motors and our controller globals here
*/
pros::Motor left_front(10);
pros::Motor left_middle(2);
pros::Motor left_back(3, true);
pros::Motor right_front(4);
pros::Motor right_middle(5);
pros::Motor right_back(6, true);

pros::Controller master(pros::E_CONTROLLER_MASTER);
	
void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	// left_front.move_absolute(100, 200);
	// pros::delay(1000);
}

void opcontrol() {
	int drive_power = 127;
	int turn_power = 50;

	while (true) {
		/**
		 * Arcade drive
		 * - left joystick for all forward back and turns
		*/
		drive_power = master.get_analog(ANALOG_LEFT_Y);
		turn_power = master.get_analog(ANALOG_LEFT_X);

		left_front.move(drive_power + turn_power);
		left_middle.move(drive_power + turn_power);
		left_back.move(drive_power + turn_power);
		right_front.move(drive_power - turn_power);
		right_middle.move(drive_power - turn_power);
		right_back.move(drive_power - turn_power);

		pros::delay(20);
	}
}
