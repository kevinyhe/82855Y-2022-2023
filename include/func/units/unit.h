#include <cmath>

#ifndef _DATATYPE_UNIT_H
#define _DATATYPE_UNIT_H

#pragma once

namespace units {
struct unit {
    double value;
    unit(double v) : value(v){};

    // in the need to do math calculations with units
    // this may lead to possible confusion between types
    operator double() const { return value; }

    void operator+=(const unit& i) { value += (double)i; }
    void operator-=(const unit& i) { value -= (double)i; }
    void operator*=(const unit& i) { value *= (double)i; }
    void operator/=(const unit& i) { value /= (double)i; }

    unit operator+(const unit& i) { return unit(value + (double)i); }
    unit operator-(const unit& i) { return unit(value - (double)i); }
    unit operator*(const unit& i) { return unit(value * (double)i); }
    unit operator/(const unit& i) { return unit(value / (double)i); }

    bool operator==(const unit& i) { return value == (double)i; }
    bool operator!=(const unit& i) { return value != (double)i; }
    bool operator>(const unit& i) { return value > (double)i; }
    bool operator<(const unit& i) { return value < (double)i; }
    bool operator>=(const unit& i) { return value >= (double)i; }
    bool operator<=(const unit& i) { return value <= (double)i; }
};
}  // namespace units

#endif  // _DATATYPE_UNIT_H