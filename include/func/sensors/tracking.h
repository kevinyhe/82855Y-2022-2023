#pragma once

#ifndef _TRACKING_WHEEL_H
#define _TRACKING_WHEEL_H

#include <array>
#include <utility>
#include "func/units/position/distance.h"

#include "datatype.h"
#include "main.h"

namespace sensors {
struct tracking_wheel {
    double diameter;
    tracking_wheel(double diameter) : diameter(diameter) {}
    virtual units::distance distance() = 0;
    virtual void reset() = 0;
};

struct ADI_tracking_wheel : public tracking_wheel {
    pros::ADIEncoder encoder;

    // initialize our tracking wheel
    /**
     * @brief Construct a new tracking wheel object
     * @param ports the ports of the encoder, in the form {top, bottom}
     * @param reversed whether the encoder is reversed
     * @param diameter the diameter of the tracking wheel
     */
    ADI_tracking_wheel(std::pair<int, int> ports,
                       bool reversed,
                       units::distance diameter)
        : encoder(std::get<0>(ports), std::get<1>(ports), reversed),
          tracking_wheel(diameter.value) {}
    /**
     * @brief get the distance travelled by the encoder (in inches)
     */
    units::distance distance() {
        return units::distance(
            double(units::angle(units::degrees(encoder.get_value()))) *
            double(diameter) / 2);
    }

    /**
     * @brief reset the encoder
     */
    void reset() { encoder.reset(); }
};
};  // namespace sensors

#endif /* _TRACKING_WHEEL_H */