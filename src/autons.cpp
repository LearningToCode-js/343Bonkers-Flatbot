#include "devices.hpp"
#include "autons.hpp"
#include "drivercontrol.hpp"
#include "EZ-Template/api.hpp"

const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;
double tileDiagonal = 67.882251;
///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void doNothing() {}

/*
┌┬┐┌─┐  ┌┬┐┌─┐┬┌─┌─┐  ┌─┐┌─┐┌┬┐┬ ┬┌─┐
 │ │ │  │││├─┤├┴┐├┤   ├─┘├─┤ │ ├─┤└─┐
 ┴ └─┘  ┴ ┴┴ ┴┴ ┴└─┘  ┴  ┴ ┴ ┴ ┴ ┴└─┘

 https://path.jerryio.com/

 1. click "file" in the top right
 2. click new file
 3. select the "static" folder in this project
 4. name the file
 5. create the path you want on the website
 6. put it as an asset below, (see line 35-40)
        example: ASSET(yourpathfile_txt)
 7. call the path using chassis.follow
        example: chassis.follow(yourpathfile_txt, 
                                timeout (do 2000), 
                                lookahead distance (do 15), 
                                isAsynchronous (should basically always be true), 
                                forwards (false makes the robot run the path backwards)
                 );
 8. call    chassis.waitUntilDist(-1);
     (this waits until the robot has finished the path)

*/

// THESE ARE THE PATH FILES, THE PATH FILES MUST BE IN THE 'static' FOLDER
// NO SD CARD REQUIRED

// function definitions

//       chassis.setPose(x, y, theta); 
//       chassis.turnTo(x, y, timeout);    
//       chassis.follow(path file, timeout, lookahead distance, isAsynchronous, forwards (false makes the robot run the path backwards));
//
//       chassis.waitUntilDist(inches); use this to have your bot wait until the path is finished
//       a really big number means just wait until the path has finished

//
// EXAMPLES OF 343X AUTOS BELOW:
//

void troll() {
  chassis.set_drive_pid(20, DRIVE_SPEED);
  stickUp();
  chassis.wait_drive();
  chassis.set_turn_pid(50, TURN_SPEED);
  chassis.wait_drive();
  stickReset();
  flywheelBackward();
  chassis.set_drive_pid(-25, DRIVE_SPEED/2);
  stick = -50;
  chassis.wait_drive();
  stickReset();
  
}

void skills() {
  stickUp();
  flywheelBackward();
  pros::delay(1400);
  stickReset();
  pros::delay(30000);
  chassis.set_drive_pid(60, DRIVE_SPEED);
  chassis.wait_until(30);
  toggleWing();
  stickDown();
  chassis.wait_until(58);
  chassis.set_turn_pid(50, TURN_SPEED);
  chassis.wait_until(48);
  stickReset();
}
void offense() {
       // Start below bar with preload on flat side
    // Drive back a little
    chassis.set_drive_pid(-5, DRIVE_SPEED); // Adjust distance as needed
    chassis.wait_until(-4);

    // Clamp down on triball underneath bar
    stickDown(); // Placeholder function for clamping action

    // Drive backwards
    chassis.set_drive_pid(-20, DRIVE_SPEED); // Adjust distance as needed
    chassis.wait_until(-18); // Cumulative distance

    // Turn -45 degrees
    chassis.set_turn_pid(-45, TURN_SPEED);
    chassis.wait_until(-43);

    // Drive backwards a little
    chassis.set_drive_pid(-15, DRIVE_SPEED);
    chassis.wait_until(-13);

    // Turn -45 degrees
    chassis.set_turn_pid(-45, TURN_SPEED); // Cumulative angle
    chassis.wait_until(-43);

    // Drive backwards and go forward a little
    chassis.set_drive_pid(-20, DRIVE_SPEED);
    chassis.wait_until(-18);
    chassis.set_drive_pid(5, DRIVE_SPEED);
    chassis.wait_until(5);

    // Turn 180 degrees
    chassis.set_turn_pid(180, TURN_SPEED); // Cumulative angle (now at 0)
    chassis.wait_until(177);

    // Drive forward a good bit and then drive back
    chassis.set_drive_pid(20, DRIVE_SPEED);
    chassis.wait_until(18);
    chassis.set_drive_pid(-24, DRIVE_SPEED);
    chassis.wait_until(-22);

    // Turn to face center middle triball
    // Assuming specific angle needed here
    chassis.set_turn_pid(45, TURN_SPEED); // Replace with actual angle
    chassis.wait_until(43);

    // Drive forward while raising stick
    stickUp(); // Placeholder function for raising stick
    chassis.set_drive_pid(30, DRIVE_SPEED);
    chassis.wait_until(14);
    stickDown();
    chassis.wait_until(28);
    pros::delay(100);
    stickReset();
    // Turn to face opponent's goal
    // Assuming specific angle needed here
    chassis.set_turn_pid(135, TURN_SPEED);
    chassis.wait_until(132);

    // Activate wing
    toggleWing(); // Placeholder function for activating wing

    // Drive backward into goal
    chassis.set_drive_pid(-20, DRIVE_SPEED);
    chassis.wait_until(-18);
    toggleWing();
    // Turn 180 degrees
    chassis.set_turn_pid(180, TURN_SPEED);
    chassis.wait_until(178); // Cumulative angle

    // Drive forward a good bit
    chassis.set_drive_pid(10, DRIVE_SPEED);
    chassis.wait_until(7);

    // Turn clockwise to face final ball
    // Assuming specific angle needed here
    chassis.set_turn_pid(30, TURN_SPEED);
    chassis.wait_until(28);

    // Drive forward while raising arm
    stickUp(); // Placeholder function for raising arm
    chassis.set_drive_pid(15, DRIVE_SPEED);
    chassis.wait_until(13);

    // Clamp down on triball
    stickDown();
    pros::delay(100);

    // Turn 180 degrees
    chassis.set_turn_pid(182, TURN_SPEED);
    chassis.wait_until(180); // Cumulative angle

    // Drive forward at full speed while raising arm
    stickUp();
    chassis.set_drive_pid(30, 127); // Using DRIVE_SPEED for full speed
    chassis.wait_until(28);
    pros::delay(500);
    stickReset();
    // End of autonomous phase

    //start below bar with preload on flat side
    //drive back a little
    //clamp down on triball underneath bar
    //drive backwards
    //turn -45
    //drive backwards a little
    //turn -45
    //drive backwards and go forward a little
    //turn 180 degrees
    //drive forward a good bit and then drive back
    //turn to face center middle triball
    //drive forward while raising stick
    //clamp down on triball
    //turn to face opponent's goal
    //activate wing
    //drive backward into goal
    //turn 180 degrees
    //drive forward a good bit
    //turn clockwise to face final ball
    //drive forward while raising arm
    //clamp down on triball
    //turn 180 degrees
    //drive forward at full speed while raising arm
    //end
    
}

void defense() {
    chassis.set_drive_pid(-50, DRIVE_SPEED); // Adjust distance as needed
    chassis.wait_until(-47);
    chassis.set_swing_pid(RIGHT_SWING, -90, TURN_SPEED);
    chassis.wait_until(-44);
    toggleWing();
    chassis.wait_until(-88);
    chassis.set_drive_pid(-27, DRIVE_SPEED); // Adjust distance as needed
    chassis.wait_until(-25);
    chassis.set_drive_pid(10, DRIVE_SPEED);
    chassis.wait_until(8);

    chassis.set_turn_pid(25, TURN_SPEED);
    chassis.wait_until(23);

    chassis.set_drive_pid(56, DRIVE_SPEED);
    chassis.wait_until(54);
    //Back at Spawn
    chassis.set_swing_pid(LEFT_SWING, 90, TURN_SPEED);
    chassis.wait_until(88);

    chassis.set_drive_pid(20, DRIVE_SPEED);
    chassis.wait_until(10);
    stickUp();
    chassis.wait_until(18);

    chassis.set_turn_pid(20, TURN_SPEED);
    chassis.wait_until(18);
    chassis.set_drive_pid(-10, DRIVE_SPEED);
    chassis.wait_until(-8);

    stickReset();
    chassis.set_swing_pid(LEFT_SWING, -90, TURN_SPEED);
    chassis.wait_until(88);
    stickDown();
    chassis.set_drive_pid(20, DRIVE_SPEED);
    chassis.wait_until(18);
    chassis.set_turn_pid(30, TURN_SPEED);
    chassis.wait_until(28);
    stickReset();
    chassis.set_drive_pid(35, DRIVE_SPEED);
    chassis.wait_drive();

    

    //start facing 90 degrees 
    //drive backward
    //swerve so that you are as close to center and to goal as possible
    //extend wings
    //drive backwards
    //turn to face away from match load center
    //drive backward at full speed while turning arm so that it goes all the way back and spinning flywheel forwards
    //drive until the triball is cleared
    //set arm just high enough to touch the horizontal bar
    //turn to face bar
    //drive forwards at full speed until touching bar
    //end
   

}

void defenseQual() {
    chassis.set_drive_pid(20, DRIVE_SPEED);
    chassis.wait_until(10);
    stickUp();
    chassis.wait_until(18);

    chassis.set_turn_pid(20, TURN_SPEED);
    chassis.wait_until(18);
    chassis.set_drive_pid(-10, DRIVE_SPEED);
    chassis.wait_until(-8);

    stickReset();
    chassis.set_swing_pid(LEFT_SWING, -90, TURN_SPEED);
    chassis.wait_until(88);
    stickDown();
    chassis.set_drive_pid(20, DRIVE_SPEED);
    chassis.wait_until(18);
    chassis.set_turn_pid(30, TURN_SPEED);
    chassis.wait_until(28);
    stickReset();
    chassis.set_drive_pid(35, DRIVE_SPEED);
    chassis.wait_drive();
}
// example auto for clearing matchload area and touching pole
void defensesafe() {
    
    chassis.set_drive_pid(-25, DRIVE_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(9, DRIVE_SPEED);
    chassis.wait_drive();
    chassis.set_turn_pid(-90, TURN_SPEED);
    chassis.wait_drive();
    stickUp();
    pros::delay(1000);
    stickReset();
}

// example auto for matchload elims
// for video check: https://www.youtube.com/live/bE180c_xft8?si=eTFYuLUq1aH28cv-&t=37856
void leftSideElims() {
    // chassis.setPose(-42.009, -55.484, 15); // X: 0, Y: 0, Heading: 0

    // chassis.follow(elimsLeftPath1_txt, 1000, 15, true);
    // // intakeOn();
    // chassis.waitUntilDist(-1);

    // pros::delay(300);

    // chassis.follow(elimsLeftPath2_txt, 1000, 15, true, false);
    // chassis.waitUntilDist(3);
    // // intake = 0;
    // chassis.waitUntilDist(-1);
    // pros::delay(350);

    // chassis.turnTo(0, -15, 1000);  
    // // intakeReverse(); 
    // pros::delay(500); 

    // chassis.follow(elimsLeftPath3_txt, 1000, 15, true);
    // chassis.waitUntilDist(-1);

    // // intake = 0;

    // chassis.follow(elimsLeftPath4_txt, 1000, 15, true, false);
    // chassis.waitUntilDist(-1);

    // chassis.turnTo(0, -35, 1000);  

    // chassis.follow(elimsLeftPath5_txt, 1000, 15, true, false);
    // chassis.waitUntilDist(-1);
}


void dothisone() {
    

}