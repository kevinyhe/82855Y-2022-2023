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

#include "compute.h"
#include "config.h"
#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"

inline u::position target(u::coord(0, 0), u::angle(0));

void reset() {
    left_encoder->reset();
    right_encoder->reset();
    back_encoder->reset();
}

void odom() {

    // struct odometry odometry(left_encoder, right_encoder, back_encoder);
    reset();

    while (true) {
        position_control();

        // odometry.compute();

        // pros::lcd::print(5, "x: %f", location.x);
        // pros::lcd::print(6, "y: %f", location.y);
        // pros::lcd::print(7, "t: %f", (double)heading * (180 / M_PI));

        pros::delay(5);
    };
};

void create_loop(double kP, double kI, double kD, double max) {
    std::vector<PID::control*> elements{
        new PID::proportional(kP, std::pair(max, -max)),
        new PID::integral(kI, std::pair(max, -max)),
        new PID::derivative(kD, std::pair(         max, -max))};
    PID::control_loop drive_PID_loop(elements, std::pair(0, 0));
}

void position_control() {
    create_loop(DRIVE_PID_P, DRIVE_PID_I, DRIVE_PID_D, PID_MAX);
    create_loop(TURN_PID_P, TURN_PID_I, TURN_PID_D, PID_MAX);

    // TODO: use odometry to update location and do math and blah blah
}

// TODO: https://pros.cs.purdue.edu/v5/tutorials/topical/adi.html#quad-encoder