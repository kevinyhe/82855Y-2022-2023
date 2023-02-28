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

#include "func/opcontrol/digital.h"
#include "config.h"
#include "main.h"
#include "pros/llemu.hpp"

/**
 * Code for all the digital buttons i.e. rollers, flywheel, expansion
 */
void digital() {
    bool button_roller = master.get_digital(button_map[ROLLER_BUTTON]);
    bool button_intake = master.get_digital(button_map[INTAKE_BUTTON]);
    bool button_flywheel = master.get_digital(button_map[FLYWHEEL_BUTTON]);
    bool button_expansion = master.get_digital(button_map[EXPANSION_BUTTON]);
    bool button_expansion_confirm =
        master.get_digital(button_map[EXPANSION_CONFIRM_BUTTON]);
    bool button_indexer = master.get_digital(button_map[INDEXER_BUTTON]);

    bool activate_expansion = button_expansion && button_expansion_confirm;

    roller.move(button_intake ? -127 : (button_roller ? 127 : 0));
    flywheel.move(button_flywheel ? -127 : 0);

    indexer.set_value(button_indexer);

    // TODO: fix this later because our code is being bitchy
    // if (!(button_expansion && button_expansion_confirm)) {
    //     expansion.set_value(false);

    // } else {
    //     expansion.set_value(true);
    // }
};