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

#include "config.h"
#include "main.h"

float turn_power_multiplier = 0.75;

/**
 * Calculate the voltage for each drive train motor.
 * This function takes the joystick values and calculates the voltage for
 * each
 * @param i The joystick value for the left joystick
 * @param j The joystick value for the right joystick
 */
std::pair<int, int> motor_voltage(float i, float j) {
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
    float L = static_cast<float>(((V + W) / 2.0)) / 100 * 127;

    // return a tuple of the left and right motor voltages
    // also cast the floats to int16 because it doesn't accept
    // floating point numbers
    return std::pair(static_cast<int>(L), static_cast<int>(R));
}

/**
 * The drive function for the bot.
 */
void drive_loop() {
    double drive_power = master.get_analog(ANALOG_LEFT_Y);
    double turn_power = master.get_analog(ANALOG_RIGHT_X) * turn_power_multiplier;
    // `motor_voltage` returns a tuple with two values
    // 0 is the left motor voltage and 1 is the right motor voltage,
    // so we use `std::tie` to assign the values to the variables
    std::pair<double, double> voltage = motor_voltage(drive_power, turn_power);
    double voltage_left = std::get<0>(voltage);
    double voltage_right = std::get<1>(voltage);

    // move the motor groups
    left_motor_group.move(voltage_left);
    right_motor_group.move(voltage_right);

    // print the voltage to the screen
    pros::lcd::print(0, "Left: %f", voltage_left);
    pros::lcd::print(1, "Right: %f", voltage_right);
}
