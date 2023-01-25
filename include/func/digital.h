#ifndef _DIGITAL_H
#define _DIGITAL_H

#include "config.h"
#include "main.h"
#include <map>

extern std::map<std::string, pros::controller_digital_e_t> _m;

extern bool b_roller;
extern bool b_flywheel;
extern bool b_expansion;
extern bool b_expansion_c;

void digital();

#endif /* _DIGITAL_H */