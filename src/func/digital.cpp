// Copyright (c) 2023 STL Robotics 82855Y

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "config.h"
#include "func/opcontrol/digital.h"
#include "main.h"

/**
 * This function maps the controller's digital buttons into strings
 * to make my life easier.
 */
std::map<std::string, pros::controller_digital_e_t> _m = {
    {"L1", DIGITAL_L1},	    {"L2", DIGITAL_L2},	      {"R1", DIGITAL_R1},
    {"R2", DIGITAL_R2},	    {"UP", DIGITAL_UP},	      {"DOWN", DIGITAL_DOWN},
    {"LEFT", DIGITAL_LEFT}, {"RIGHT", DIGITAL_RIGHT}, {"X", DIGITAL_X},
    {"B", DIGITAL_B},	    {"Y", DIGITAL_Y},	      {"A", DIGITAL_A},
};

/**
 * Code for all the digital buttons i.e. rollers, flywheel, expansion
 */
void digital() {
	bool b_roller = master.get_digital(_m["L1"]);
	bool b_flywheel = master.get_digital(_m["L2"]);
	bool b_expansion = master.get_digital(_m["A"]);
	bool b_expansion_c = master.get_digital(_m["LEFT"]);

	roller.move(b_roller ? -127 : 0);
	flywheel.move(b_flywheel ? -127 : 0);
};