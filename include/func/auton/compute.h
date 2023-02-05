#ifndef _ODOM_COMPUTE_H
#define _ODOM_COMPUTE_H

#include <utility>
#include "config.h"
#include "datatype.h"
#include "func/sensors/tracking.h"
#include "func/units/angle/angle.h"
#include "func/units/position/distance.h"
#include "main.h"
#include "pros/llemu.hpp"

#pragma once

struct odometry {
    /**
     * sL is the left-right distance from the tracking center to the left
     * tracking wheel sR is the left-right distance from the tracking center to
     * the right tracking wheel sS is the forward-backward distance from the
     * tracking center to the back tracking wheel
     * d0 is the previous global position vector
     * theta1 is the new absolute orientation
     * theta0 is the previous global orientation
     * thetaR is the global orientation at last reset
     */
    sensors::ADI_tracking_wheel* left_wheel;
    sensors::ADI_tracking_wheel* right_wheel;
    sensors::ADI_tracking_wheel* back_wheel;
    units::distance sL = LEFT_ENCODER_DISTANCE;
    units::distance sR = RIGHT_ENCODER_DISTANCE;
    units::distance sS = BACK_ENCODER_DISTANCE;

    units::distance d0 = 0;
    units::angle theta1 = 0;
    units::angle theta0 = 0;
    units::angle thetaR = 0;

    units::distance lastL = 0;
    units::distance lastR = 0;
    units::distance lastS = 0;

    // make sure to initialize the tracking wheels with new so it allows for
    // polymorphism
    odometry(sensors::ADI_tracking_wheel* l,
             sensors::ADI_tracking_wheel* r,
             sensors::ADI_tracking_wheel* b) {
        this->left_wheel = l;
        this->right_wheel = r;
        this->back_wheel = b;
    }

    // bitch ass position calculation
    // https://pos.tixo.ca !!! use this
    units::position compute(units::position initial) {
        // position tracking works by modelling the motion of the
        // tracking center as an arc over an infinitely short time interval.
        // the arc angle is the same as the change of orientation in the robot.
        // we will call this angle `delta_theta` and we can calculate the
        // changes in the left and right side with the distance travelled by the
        // left and right encoders. use the standard arc length formula, then
        // combine to eliminate the radius of the "circle" (motion of tracking
        // center)
        units::distance dL = left_wheel->distance() - lastL;
        units::distance dR = right_wheel->distance() - lastR;
        units::distance dS = back_wheel->distance() - lastS;

        lastL = dL;
        lastR = dR;
        lastS = dS;

        theta0 = initial._angle;

        // this will give a value in radians
        // our orientation can be calculated as an absolute quantity
        // rtather than a relative change bceause it applies regardless
        // of where the robot is on the field
        units::angle theta1 =
            thetaR + units::angle(double(dL - dR) / double(sL + sR));
        units::angle dT = theta1 - theta0;

        units::coord local_offset;

        if (double(dT) == 0) {
            // this means the robot has not turned, so `dL` = `dR`
            // calculate local offset
            local_offset = units::coord(dS, dR);
        } else {
            // 
            units::distance local_offset_x =
                double(2 * sin(double(dT) / 2) * ((dS / dT) + sS));
            units::distance local_offset_y =
                double(2 * sin(double(dT) / 2) * ((dR / dT) + sR));
            local_offset = units::coord(local_offset_x, local_offset_y);
        }

        // calculate average orientation
        units::angle thetaM = theta0 + units::angle(double(dT) / 2);

        // calculate global offset
        std::pair<double, units::angle> polar_global_offset =
            to_polar(local_offset);
        units::angle polar_global_orientation =
            polar_global_offset.second + thetaM;
        units::coord global_offset =
            to_cartesian(polar_global_offset.first, polar_global_orientation);
        initial += global_offset;
        initial._angle += dT;
        thetaR = initial._angle;
        return initial;
    };

    // polar coordinates are determined by a distance from a reference
    // point and an angle from a reference direction. in our case, polar
    // coordinates can be used to express a vector of the bot's translation
    // with a magnitude and direction. this is useful for calculating the
    // bot's position in the field.
    std::pair<double, units::angle> to_polar(units::coord c) {
        double rho = sqrt(pow(c.x, 2) + pow(c.y, 2));
        units::angle theta = units::angle(atan2(c.y, c.x));
        return std::pair<double, units::angle>(rho, theta);
    }

    // convert polar coordinates back to cartesian coordinates
    units::coord to_cartesian(double rho, units::angle theta) {
        units::coord c;
        c.x = rho * cos(theta);
        c.y = rho * sin(theta);
        return c;
    }
};

#endif /* _ODOM_COMPUTE_H */