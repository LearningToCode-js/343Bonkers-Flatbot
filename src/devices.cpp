#include "main.h"
#include "devices.hpp"
#include "drivercontrol.hpp"
#include "EZ-Template/api.hpp"

// this stuff is for example autos, you should get rid of this and add your own devices here
bool wingsOut = false;
bool intakeOut = false;
bool ptoOn4bar = false;
bool isFlywheelForward = false;
bool parkOut = false;
// this stuff is for example autos, you should get rid of this and add your own devices here

pros::ADIDigitalOut wing1('B');
pros::ADIDigitalOut wing2('A');
pros::ADIDigitalOut intake1 ('C');
pros::ADIDigitalOut intake2 ('E');
pros::ADIDigitalOut pto ('D');
pros::ADIDigitalOut park ('F');
// this stuff is for example autos, you should get rid of this and add your own devices here

pros::Motor stick (15, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
// pros::Motor intake (17, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor flywheel (5, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
// this stuff is for example autos, you should get rid of this and add your own devices here


// set up your motors here but try not to change the names
// DO NOT CHANGE NAMES
pros::Motor leftFront(15, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor leftBack(16, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor leftTop(17, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor rightFront(6, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor rightBack(7, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor rightTop(8, pros::E_MOTOR_GEARSET_06, false); 
// DO NOT CHANGE NAMES

pros::MotorGroup left_side_motors({leftFront, leftBack, leftTop});
pros::MotorGroup right_side_motors({rightFront, rightFront, rightTop});

pros::Imu inertial_sensor(19); 

pros::Controller master(pros::E_CONTROLLER_MASTER);


Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {16, 18, -19}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{6, 8, -9}

  // IMU Port
  ,19

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.666

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);







// lemlib::Drivetrain_t drivetrain {
//     &left_side_motors, // left drivetrain motors
//     &right_side_motors, // right drivetrain motors
//     11, // track width
//     3.25, // wheel diameter
//     360, // wheel rpm
//     2 // chase power
// };

// lemlib::OdomSensors_t sensors {
//     nullptr, 
//     nullptr, 
//     nullptr, 
//     nullptr,
//     &inertial_sensor // inertial sensor
// };

// // forward/backward PID
// lemlib::ChassisController_t lateralController {
//     0.45, // kP
//     5, // kD
//     1, // smallErrorRange
//     80, // smallErrorTimeout
//     3, // largeErrorRange
//     300, // largeErrorTimeout
//     7 // slew rate
// };
 
// // turning PID
// lemlib::ChassisController_t angularController {
//     5, // kP
//     35, // kD
//     1, // smallErrorRange
//     100, // smallErrorTimeout
//     3, // largeErrorRange
//     500, // largeErrorTimeout
//     0 // slew rate
// };

// lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);
