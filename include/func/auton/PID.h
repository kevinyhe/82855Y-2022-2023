#ifndef _PID_H
#define _PID_H

#include <vector>

#include "datatype.h"
#include "main.h"

#pragma once

namespace PID {
// this is the base class for all of our PID elements
struct control {
    // our k value is the factor that we multiply by
    double k;
    control(double f) : k(f){};

    virtual double compute(double t, double c) = 0;
};

// computes values for a set of `control` elements
struct control_loop {
    // initialize a vector of `control` elements
    std::vector<control*> control_set;

    double min;
    double max;

    /**
     * @brief Construct a new control loop object
     * @param v the vector of `control` elements
     * @param m the minimum and maximum values that the output can be
    */
    control_loop(std::vector<control*> v, std::pair<double, double> m)
        : control_set(v) {
        // initialize the vector and assign it to `control_set`
        min = std::get<0>(m);
        max = std::get<1>(m);
    }

    double clamp(double v) { return (v <= max) ? ((v >= min) ? v : min) : max; }

    double update(double t, double c) {
        double output = 0;
        // iterate through the elements in the vector and add the return value
        // of `compute`
        for (control* i : control_set) {
            // get the member `compute` from the struct that `i` points to
            // so in this case it'll be the control element's `compute` function
            output += i->compute(t, c);
        }
        return clamp(output);
    }
};

struct proportional : public control {
    double max;
    double min;

    // our f value is the factor, so kD
    // our max and our min are the maximum and minimum values, basically
    // the caps on the output. this will be especially useful when
    // dealing with the integral value
    proportional(double f, std::pair<double, double> m) : control(f) {
        max = std::get<0>(m);
        min = std::get<1>(m);
    }

    double clamp(double v) { return (v <= max) ? ((v >= min) ? v : min) : max; }

    // take the sensor data and subtract the target
    // to end up with our error (t - c), basically the amount that the robot
    // is overshooting or undershooting compared to what we want
    // assuming we live in a world with no friction and the exact same
    // battery voltage, err would be 0, but other factors will either
    // cause our robot to vary from what we want
    double compute(double target, double current) {
        // note: we use target - current so we assume that the offset
        // is in the correct direction already
        double v = k * (target - current);
        // clamp the value between the min and max, if it's less than the min,
        // return the min, if it's greater than the max, return the max
        return clamp(v);
    }
};

struct integral : public control {
    double total_err = 0;  // total error value (accumulation of error)
    double max;
    double min;

    // if we do not specifiy a max or a min, there is the possibility
    // for integral windup, which is when the integral will grow and grow
    // without any limit. the maximum and minimum are in place to prevent
    // this from happening
    integral(double f, std::pair<double, double> m) : control(f) {
        max = std::get<0>(m);
        min = std::get<1>(m);
    }

    double clamp(double v) { return (v <= max) ? ((v >= min) ? v : min) : max; }

    // convert velocity -> position -> absement to detect if it's going too
    // slow. absement is the measure of sustained displacement of an object from
    // its initial position, so if the position is not reaching the target over
    // a certain period of time it will continue to repeatedly add the error
    // over and over again
    double compute(double target, double current) {
        // if we have already reached the target (to within a small degree of
        // error) then there's no need to go through this calculation again
        if ((int)target == int(current)) {
            total_err = 0;
            return 0;
        }
        // note: we use target - current so we assume that the offset
        // is in the correct direction already
        total_err += target - current;
        double v = k * total_err;
        return clamp(v);  // clamp value
    }
};

struct derivative : public control {
    double prev_err = 0;  // previous error value
    double max;
    double min;

    derivative(double f, std::pair<double, double> m) : control(f) {
        max = std::get<0>(m);
        min = std::get<1>(m);
    }

    double clamp(double v) { return (v <= max) ? ((v >= min) ? v : min) : max; }

    // derivative is the change between the error and the previous error
    // so if the bot goes too fast, derivative will have a negative effect
    // if it goes too slow, it will have a positive effect, so it will
    // speed up and slow down the robot based on its speed
    double compute(double target, double current) override {
        // note: we use target - current so we assume that the offset
        // is in the correct direction already
        double v = k * (target - current - prev_err);
        prev_err = target - current;

        return clamp(v);  // clamp value
    }
};
}  // namespace PID

#endif /* _PID_H */