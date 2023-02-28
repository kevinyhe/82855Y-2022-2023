#include <cmath>

#ifndef _DATATYPE_DISTANCE_H
#define _DATATYPE_DISTANCE_H

#pragma once

#include "../unit.h"

namespace u {
    struct distance : public unit {
        // default units are `inches`
        // returns 0 on default
        distance() : unit(0){};
        // constructor, intializes value of a member variable
        // called unit
        distance(double value) : unit(value){};

        void operator+=(const distance& i) { value += (double)i; }
        void operator-=(const distance& i) { value -= (double)i; }
        void operator*=(const distance& i) { value *= (double)i; }
        void operator/=(const distance& i) { value /= (double)i; }

        distance operator+(const distance& i) {
            return distance(value + (double)i);
        }
        distance operator-(const distance& i) {
            return distance(value - (double)i);
        }
        distance operator*(const distance& i) {
            return distance(value * (double)i);
        }
        distance operator/(const distance& i) {
            return distance(value / (double)i);
        }
    };

    struct inches : public distance {
        inches(double v) : distance(v){};
    };
}  // u

#endif  // _DATATYPE_DISTANCE_H