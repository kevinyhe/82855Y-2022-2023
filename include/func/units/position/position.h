#include "func\units\angle\angle.h"
#include "func\units\position\coord.h"

#ifndef DATATYPE_POSITION_H
#define DATATYPE_POSITION_H

#pragma oncef

namespace u {
struct position : public coord {
    angle _angle;
    position(coord vector, angle angle) : coord(vector), _angle(angle){};

    operator angle() { return _angle; }
};
}  // namespace units

#endif /* DATATYPE_POSITION_H */