#pragma once

#include "main.h"
#include "EZ-Template/api.hpp"

extern pros::Controller master;

// extern pros::Motor intake;
extern pros::Motor stick;
extern pros::Motor flywheel;

extern pros::Motor rightFront;
extern pros::Motor rightBack;
extern pros::Motor rightTop;

extern pros::Motor leftFront;
extern pros::Motor leftBack;
extern pros::Motor leftTop;

extern pros::ADIDigitalOut wing1;
extern pros::ADIDigitalOut wing2;
extern pros::ADIDigitalOut intake1;
extern pros::ADIDigitalOut intake2;
extern pros::ADIDigitalOut pto;
extern pros::ADIDigitalOut park;

extern bool wingsOut;
extern bool intakeOut;
extern bool ptoOn4bar;
extern bool isFlywheelForward;
extern bool parkOut;

// extern lemlib::Chassis chassis;
extern Drive chassis;
