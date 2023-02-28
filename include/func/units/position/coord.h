#include <tuple>

#include "distance.h"

#pragma once

#ifndef _DATATYPE_COORD_H
#define _DATATYPE_COORD_H

namespace u {
    struct coord {
        distance x;
        distance y;
        distance length;

        coord() : x(0), y(0), length(0){};
        coord(distance x, distance y) : x(x), y(y), length(update_length()){};
        coord(std::pair<distance, distance> t)
            : x(std::get<0>(t)), y(std::get<1>(t)), length(update_length()){};

        void operator+=(const coord& i) {
            x += i.x;
            y += i.y;
            length = update_length();
        }
        void operator-=(const coord& i) {
            x -= i.x;
            y -= i.y;
            length = update_length();
        }

        coord operator+(const coord& i) { return coord(x + i.x, y + i.y); }
        coord operator-(const coord& i) { return coord(x - i.x, y - i.y); }

        // relative coord calculation from inital position to final position
        coord(coord i, coord f)
            : x(f.x - i.x), y(f.y - i.y), length(update_length()){};

        distance update_length() {
            length = sqrt((x * x) + (y * y));
            return length;
        }
    };
}  // u

#endif  // _DATATYPE_COORD_H