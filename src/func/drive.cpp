#include "func/drive.h"
#include "config.h"
#include "main.h"

float turn_power_multiplier = 0.5;

/**
 * Calculate the voltage for each drive train motor.
 * This function takes the joystick values and calcul ates the voltage for
 * each
 * @param i The joystick value for the left joystick
 * @param j The joystick value for the right joystick
 */
std::tuple<int, int> motor_voltage(float i, float j)
{
    // because readings of the analog channel range from -127 to
    // 127 scale the joystick values to be between -100 and 100
    // so, we will use a percentage from -100% to 100%
    // first we cast the int to a float, then divide by 127
    // and multiply by 100 to get a percentage of full power
    float Y = (static_cast<float>(i) / 127.0) * 100;
    float X = (static_cast<float>(j) / 127.0) * 100;

    // please refer to this, I don't know how to explain it
    // https://home.kendra.com/mauser/Joystick.html
    int V = (100 - abs(int(X))) * (Y / 100) + Y;
    int W = (100 - abs(int(Y))) * (X / 100) + X;

    float R = static_cast<float>(((V - W) / 2.0)) / 100 * 127;
    float L = static_cast<float>(((V + W) / 2.0)) / 100 * 127;

    // return a tuple of the left and right motor voltages
    // also cast the floats to int16 because it doesn't accept
    // floating point numbers
    return std::make_tuple(static_cast<int>(L), static_cast<int>(R));
}

/**
 * The drive function for the bot.
 */
void drive()
{
    drive_power = master.get_analog(ANALOG_LEFT_Y);
    turn_power = master.get_analog(ANALOG_RIGHT_X) * turn_power_multiplier;
    // `motor_voltage` returns a tuple with two values
    // 0 is the left motor voltage and 1 is the right motor voltage
    // so we use `std::tie` to assign the values to the variables
    std::tie(voltage_left, voltage_right) =
	motor_voltage(drive_power, turn_power);

    // move the motor groups
    left_motor_group.move(voltage_left);
    right_motor_group.move(voltage_right);

    pros::lcd::print(1, "v_l: %d", voltage_left);
    pros::lcd::print(2, "v_r: %d", voltage_right);
}