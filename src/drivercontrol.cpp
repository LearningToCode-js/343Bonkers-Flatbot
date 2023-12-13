#include "main.h"
#include "drivercontrol.hpp"
#include "devices.hpp"
#include "pros/rtos.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "EZ-Template/api.hpp"

// . . .
// 
//  DRIVER CONTROL
//
// . . .

void set_drive_to_coast() {
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftTop.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightTop.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void set_drive_to_hold() {
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightTop.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

double left_curve_function(double x, double left_curve_scale) {
  if (left_curve_scale != 0) {
    // if (CURVE_TYPE)
    return (powf(2.718, -(left_curve_scale / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(left_curve_scale / 10)))) * x;
    // else
    // return powf(2.718, ((abs(x)-127)*RIGHT_CURVE_SCALE)/100)*x;
  }
  return x;
}

void set_tank(int l_stick, int r_stick) {
    leftFront.move_voltage(l_stick * (12000.0 / 127.0));
    leftBack.move_voltage(l_stick * (12000.0 / 127.0));
    leftTop.move_voltage(l_stick * (12000.0 / 127.0));

    rightFront.move_voltage(r_stick * (12000.0 / 127.0));
    rightBack.move_voltage(r_stick * (12000.0 / 127.0));
    rightTop.move_voltage(r_stick * (12000.0 / 127.0));
}

void tank_drive(double curve) {
    // Put the joysticks through the curve function
    int l_stick = left_curve_function(master.get_analog(ANALOG_LEFT_Y), curve);
    int r_stick = left_curve_function(master.get_analog(ANALOG_RIGHT_Y), curve);

    // Set robot to l_stick and r_stick, check joystick threshold, set active brake
    set_tank(l_stick, r_stick);
}

// void togglePto() {
//   ptoOn4bar = !ptoOn4bar;
//   pto.set_value(ptoOn4bar);
// }

void setStickToHold() {
  stick.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  // intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); // putting this here because the intake is the same as 4b motor
}

void setIntakeToCoast() {
  stick.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); 
  // fourBar.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); // putting this here because the intake is the same as 4b motor
}

void stickUp() {
  // if (!ptoOn4bar) {
  //   togglePto();
  //   setStickToHold();
  // }

  stick = 127;
}

void stickDown() {
  // if (!ptoOn4bar) {
  //   togglePto();
  //   setStickToHold();
  // }

  stick = -127;
}

void stickReset() {
  stick.move_velocity(0);
}

void flywheelForward() {
  flywheel = -127;
}

void flywheelBackward() {
  flywheel = 127;
}

void flywheelReset() {
  flywheel = 0;
  isFlywheelForward = false;
}

void toggleIntake() {
  intakeOut = !intakeOut;
  intake1.set_value(intakeOut);
  intake2.set_value(intakeOut);
  pros::delay(200);
}

void toggleWing() {
  wingsOut = !wingsOut;
  wing1.set_value(wingsOut);
  wing2.set_value(wingsOut);
  pros::delay(200);
}
