#include <cmath>

#include "../unit.h"

#ifndef _DATATYPE_ANGLE_H
#define _DATATYPE_ANGLE_H

#pragma once

namespace u {
    struct angle : public unit {
        // default units are `radians`
        angle() : unit(0){};
        angle(double value) : unit(value){};

        operator double() const { return value; }

        void operator+=(const angle& i) { value += (double)i; }
        void operator-=(const angle& i) { value -= (double)i; }
        void operator*=(const angle& i) { value *= (double)i; }
        void operator/=(const angle& i) { value /= (double)i; }

        angle operator+(const angle& i) { return angle(value + (double)i); }
        angle operator-(const angle& i) { return angle(value - (double)i); }
        angle operator*(const angle& i) { return angle(value * (double)i); }
        angle operator/(const angle& i) { return angle(value / (double)i); }
    };

    struct degrees : public angle {
        // M_PI is defined in math.h as 3.14159265358979323846
        degrees(double v) : angle(v * M_PI / 180){};
    };

    struct radians : public angle {
        radians(double v) : angle(v){};

        // constrains the angle values into the range of 0 to 2PI
        void prune() {
            // if divison by zero then set angle to 0
            if (isnanf(value) || isinff(value))
                value = 0;

            // ensure that the angle is kept in the range of 0 to 2PI
            value = fmod(fmod(value, 2 * M_PI) + 2 * M_PI, 2 * M_PI);
        }
    };
}  // u

#endif  // _DATATYPE_ANGLE_H