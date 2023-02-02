#ifndef _ODOM_COMPUTE_H
#define _ODOM_COMPUTE_H

#include "config.h"
#include "datatype.h"
#include "main.h"

#pragma once

struct odometry {
    units::distance dist_L;
    units::distance dist_R;
    units::distance dist_B;

    // define with new because we need static memory and polymorphism
    odometry(units::distance dX, units::distance dY, units::distance dB) {
        this->dist_L = dX;
        this->dist_R = dY;
        this->dist_B = dB;
    }

    // bitch ass position calculation
    units::position compute(units::position initial,
                                     units::distance R,
                                     units::distance L,
                                     units::distance S) {
        units::distance delta_f = double(R + L) / 2;
        units::angle delta_theta =
            double(R - L) /
            double(LEFT_ENCODER_DISTANCE - RIGHT_ENCODER_DISTANCE);
        units::distance delta_s =
            double(double(S) - (BACK_ENCODER_DISTANCE * double(delta_theta)));

        double r0 = double(delta_f) / double(delta_theta);
        double r1 = double(delta_s) / double(delta_theta);

        double rel_delta_x = (r0 * sin(delta_theta)) - (r1 * cos(delta_theta));
        double rel_delta_y = (r1 * sin(delta_theta)) - (r0 * cos(delta_theta));

        double x = double(initial.x) + (rel_delta_x * cos(initial._angle)) -
                   (rel_delta_y * sin(initial._angle));
        double y = double(initial.y) + (rel_delta_y * cos(initial._angle)) +
                   (rel_delta_x * sin(initial._angle));

        return units::position(
            std::pair(units::distance(x), units::distance(y)),
            initial._angle + delta_theta);
    };
};

#endif /* _ODOM_COMPUTE_H */