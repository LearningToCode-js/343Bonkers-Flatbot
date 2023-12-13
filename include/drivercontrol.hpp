#pragma once

#include "pros/rtos.hpp"
#include "EZ-Template/api.hpp"



// . . .
// 
//  DRIVER CONTROL
//
// . . .
void togglePto();
void setStickToHold();
void setIntakeToCoast();
void stickUp();
void stickDown();
void stickReset();
void toggleIntake();
void toggleWing();
void flywheelForward();
void flywheelBackward();
void flywheelReset();

void tank_drive(double curve = 4.0);
void set_drive_to_coast();
void set_drive_to_hold();

