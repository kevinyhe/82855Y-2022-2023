#ifndef _DIGITAL_H
#define _DIGITAL_H

#include "main.h"
#include <map>

extern bool b_roller;
extern bool b_flywheel;
extern bool b_expansion;
extern bool b_expansion_c;

extern std::map<std::string, pros::controller_digital_e_t> _m;

void digital();

#endif /* _DIGITAL_H */