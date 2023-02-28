#ifndef _ODOM_COMPUTE_H
#define _ODOM_COMPUTE_H

#include <utility>
#include "config.h"
#include "datatype.h"
#include "func/sensors/tracking.h"
#include "func/units/angle/angle.h"
#include "func/units/position/coord.h"
#include "func/units/position/distance.h"
#include "main.h"
#include "pros/llemu.hpp"

#pragma once

// nightmare nightmare nightmare
struct odometry {
    /**
     * sL is the left-right distance from the tracking center to the left
     * tracking wheel sR is the left-right distance from the tracking center
     to
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
    u::distance sL = LEFT_ENCODER_DISTANCE;
    u::distance sR = RIGHT_ENCODER_DISTANCE;
    u::distance sS = BACK_ENCODER_DISTANCE;

    u::distance d0 = 0;
    u::angle theta1 = 0;
    u::angle theta0 = 0;
    u::angle thetaR = 0;

    u::distance lastL = 0;
    u::distance lastR = 0;
    u::distance lastS = 0;

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
    void compute() {
        // position tracking works by modelling the motion of the
        // tracking center as an arc over an infinitely short time interval.
        // the arc angle is the same as the change of orientation in the robot.
        // we will call this angle `delta_theta` and we can calculate the
        // changes in the left and right side with the distance travelled by the
        // left and right encoders. use the standard arc length formula, then
        // combine to eliminate the radius of the "circle" (motion of tracking
        // center)
        u::distance dL_r = left_wheel->distance();
        u::distance dR_r = right_wheel->distance();
        u::distance dS_r = back_wheel->distance();

        u::distance dL = dL_r - lastL;
        u::distance dR = dR_r - lastR;
        u::distance dS = dS_r - lastS;

        // update the last position values
        lastL = dL_r;
        lastR = dR_r;
        lastS = dS_r;
        
        // we can represent the robot's motion as a triangle with the two legs
        // being the left and right wheel displacements and the hypotenuse being
        // the total displacement of the robot. we can use the law of sines to
        // find the hypotenuse. the angle of the hypotenuse is the change in
        // orientation of the robot. we can use the law of cosines to find the
        // angle of the hypotenuse. we can then use the angle of the hypotenuse
        // to find the x and y components of the displacement of the robot.
        // we can then add the x and y components to the current position to
        // find the new position.

        // also note that the triangle formed by the arc is isosceles

        u::distance h; // hypotenuse that gives total displacement of robot
        u::distance h2; 
        u::angle theta = double(dL - dR) / (sL + sR);
        u::angle i; // half of a, the increase in current heading

        // change in bearing
        if (theta) {
            // radius of the circle that the robot travels with its right wheel
            u::distance radius = (double)dR / theta;
            i = (double)theta / 2.0;
            h = 2.0 * (double(radius + sR) * sin(i));

            u::distance radiusB =
                (double)dS / theta;  // radius of the circle that the robot
                                     // travels with its back wheel.
            h2 = 2.0 * (double(radiusB + sS) * sin(i));
        } else { // no change in bearing
            h = dR;
            i = 0;
            h2 = dS;
        }

        // angle of movement but not the final angle position
        u::angle ma = i + heading; 

        // updates the global position
        location.y += double(h) * cos(ma);
        location.x += double(h) * sin(ma);

        // drift correction to the global position
        location.y += (double)h2 * -sin(ma);
        location.x += (double)h2 * cos(ma);

        heading += theta;  // updates the current global angle

        // constrain the angle
        heading = wrap(heading);
    }

    // wrap angles between 0 and 2PI degrees
    u::angle wrap(u::angle v) {
        // division by zero is undefined, so we need to check for it
        if (isnanf(v) || isinff(v))
            v = 0;
        // conform to normal modulus rules so that negative numbers
        return fmod(fmod(v, 2 * M_PI) + 2 * M_PI, 2 * M_PI);
    }
};

#endif /* _ODOM_COMPUTE_H */