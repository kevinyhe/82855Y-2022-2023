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

inline units::position target(units::coord(0, 0), units::angle(0));

void reset() {
    left_encoder->reset();
    right_encoder->reset();
    back_encoder->reset();
}

void odom() {
    reset();

    struct odometry odometry(left_encoder, right_encoder, back_encoder);

    while (true) {
        position_control();

        location = odometry.compute(location);

        pros::lcd::print(5, "x_location: %d", location.x);
        pros::lcd::print(6, "y_location: %d", location.y);
        pros::lcd::print(7, "theta_location: %d", location._angle);

        pros::delay(20);
    };
};

void position_control() {
    std::vector<PID::control*> drive_PID_elements{
        new PID::proportional(DRIVE_PID_D, std::pair(PID_MAX, -PID_MAX)),
        new PID::integral(DRIVE_PID_I, std::pair(PID_MAX, -PID_MAX)),
        new PID::derivative(DRIVE_PID_P, std::pair(PID_MAX, -PID_MAX))};
    PID::control_loop drive_PID_loop(drive_PID_elements, std::pair(0, 0));

    std::vector<PID::control*> turn_PID_elements{
        new PID::proportional(DRIVE_PID_D, std::pair(PID_MAX, -PID_MAX)),
        new PID::integral(DRIVE_PID_I, std::pair(PID_MAX, -PID_MAX)),
        new PID::derivative(DRIVE_PID_P, std::pair(PID_MAX, -PID_MAX))};
    PID::control_loop turn_PID_loop(turn_PID_elements, std::pair(0, 0));

    // TODO: use odometry to update location and do math and blah blah
}

// TODO: https://pros.cs.purdue.edu/v5/tutorials/topical/adi.html#quad-encoder