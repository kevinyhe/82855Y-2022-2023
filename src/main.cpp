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
pros::Motor left_front(10, true);
pros::Motor left_middle(2, true); // we don't know why this is reversed it's just like that
pros::Motor left_back(3, true);
pros::Motor right_front(4);
pros::Motor right_middle(5);
pros::Motor right_back(6, true);
pros::Motor roller(9);
pros::Motor expan(11);//temporary, depends on where we attach expansion
pros::Controller master(pros::E_CONTROLLER_MASTER);
	
void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	left_front.move_absolute(100, 100); // Moves 100 units forward
  	while (!((left_front.get_position() < 105) && (left_front.get_position() > 95))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
 	   pros::delay(2);
	}
	left_front.move_relative(100, 100); // Also moves 100 units forward
  	while (!((left_front.get_position() < 205) && (left_front.get_position() > 195))) {
    	pros::delay(2);
  	 }
	// left_front.move_absolute(100, 200);
	// pros::delay(1000);
}

void opcontrol() {
	int drive_power = 60;
	int turn_power = 50;
	bool roller_button = false;
	bool expan_button = false;
	bool Auto_button = false;
	while (true) {
		/**
		 * Arcade drive
		 * - left joystick for all forward back and turns
		*/
		drive_power = master.get_analog(ANALOG_LEFT_Y);
		turn_power = master.get_analog(ANALOG_RIGHT_X);
		roller_button = master.get_digital(DIGITAL_L1);
		expan_button = master.get_digital(DIGITAL_L2);

		

		//expansion
		if (expan_button) {
			expan.move(60);
		} else {
			expan.move(0);
		}

		//roller
		if (roller_button) {
			roller.move(120); 
		} else {
			roller.move(0); 
		}
		/**
		 * things to do:
		 * one joystick for forward back and turning
		 * turns way too fast
		 * autonomous
		 * different speed modes?
		*/

		left_front.move(drive_power + turn_power);
		left_middle.move(drive_power + turn_power);
		left_back.move(drive_power + turn_power);
		right_front.move(drive_power - turn_power);
		right_middle.move(drive_power - turn_power);
		right_back.move(drive_power - turn_power);

		pros::delay(20);

    	// std::cout << "Left Front Motor Position: " << left_front.get_position();
		// left_middle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	// std::cout << "Left Middle Position: " << left_middle.get_position();
		// left_back = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	// std::cout << "Left Back Motor Position: " << left_back.get_position();
		// right_front = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	// std::cout << "Right Front Motor Position: " << right_front.get_position();
		// right_middle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	// std::cout << "Right Middle Motor Position: " << right_middle.get_position();
		// right_back = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	// std::cout << "Right Back Motor Position: " << right_back.get_position();		
	}
}
