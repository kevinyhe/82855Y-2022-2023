#include "config.h"
#include "func/auton/compute.h"
#include "main.h"
#include "pros/motors.h"

u::coord location(0, 0);
u::angle heading(0);

/**
 * This function maps the controller's digital buttons into strings
 * to make my life easier.
 */
std::map<std::string, pros::controller_digital_e_t> button_map = {
    {"L1", DIGITAL_L1},     {"L2", DIGITAL_L2},       {"R1", DIGITAL_R1},
    {"R2", DIGITAL_R2},     {"UP", DIGITAL_UP},       {"DOWN", DIGITAL_DOWN},
    {"LEFT", DIGITAL_LEFT}, {"RIGHT", DIGITAL_RIGHT}, {"X", DIGITAL_X},
    {"B", DIGITAL_B},       {"Y", DIGITAL_Y},         {"A", DIGITAL_A},
};

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(PORT_LEFT_FRONT, true);
pros::Motor left_middle(PORT_LEFT_MIDDLE, true);
pros::Motor left_back(PORT_LEFT_BACK, true);

pros::Motor right_front(PORT_RIGHT_FRONT);
pros::Motor right_middle(PORT_RIGHT_MIDDLE);
pros::Motor right_back(PORT_RIGHT_BACK);

pros::Motor_Group left_motor_group({left_front, left_middle, left_back});
pros::Motor_Group right_motor_group({right_front, right_middle, right_back});

pros::Motor roller(PORT_ROLLER);

pros::Motor flywheel(PORT_FLYWHEEL);

pros::ADIDigitalOut indexer(INDEXER_ADI);
pros::ADIDigitalOut expansion(EXPANSION_ADI);
// pros::ADIDigitalOut expansion({{11, 'F'}});

sensors::ADI_tracking_wheel* left_encoder =
    new sensors::ADI_tracking_wheel(LEFT_TRACKING_PORT, true, WHEEL_DIAMETER);
sensors::ADI_tracking_wheel* right_encoder =
    new sensors::ADI_tracking_wheel(RIGHT_TRACKING_PORT, true, WHEEL_DIAMETER);
sensors::ADI_tracking_wheel* back_encoder =
    new sensors::ADI_tracking_wheel(BACK_TRACKING_PORT, false, WHEEL_DIAMETER);