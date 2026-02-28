#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "robotConfig.h"
#include <cstdio>

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors

    // thread to for brain screen and position logging
    //pros::Task screenTask([&]() {
      //  while (true) {
            // print robot location to the brain screen
        //    pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
        //    pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
        //    pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
        //    lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
        //    pros::delay(50);
        //}
    //});
}

/**
 * Runs while the robot is disabled
 */
void disabled() {}

/**
 * runs after initialize if the robot is connected to field control
 */
void competition_initialize() {}

/**
 * Runs during auto
 */

 /*
 ### STRATEGY ###
 */
void autonomous(void) {
    chassis.moveToPoint(0, 47, 10000,{ .maxSpeed = 60 });//move to first point
    chassis.turnToHeading(-45, 1000,{ .maxSpeed = 60 });//spin towards the goal
    chassis.setPose(0, 0, 0);//set to 0
    chassis.moveToPoint(0, 5, 1000,{ .maxSpeed = 60 });//move to second point
    conveyorMotor.move(-127);
    intakeMotor.move(-127);
    pros::delay(4000);//wait till the blocks out
    conveyorMotor.move(-0);
    intakeMotor.move(-0);
    chassis.setPose(0, 0, 0);//set to 0
    chassis.moveToPoint(0, 5, 1000,{ .maxSpeed = 60 });//move to second point
    chassis.setPose(0, 0, 0);//set to 0
    chassis.moveToPoint(0, -5, 1000,{.forwards = false, .maxSpeed = 60 });//move to second point
    conveyorMotor.move(-0);
    intakeMotor.move(-0);




}

/**
 * Runs in driver control
 */

void opcontrol() {
    // controller
    // loop to continuously update motors

    //variables
    bool intaking = false;//is the spinner spinning forwad?
    bool spitting = false;//is the spinner spinning backwards?
    bool turnning = false;//is the 'emptier' turning?
    spinMotor.set_zero_position(0); //set the spin motor base position (left side facing)
    //int speed = 127;
    double spot = -200;


    while (true) {
		//button code
        // get joystick positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        // move the chassis with curvature drive
        chassis.tank(leftY, rightX);

        //intake motor code
        //get_digital(DIGITAL_L1)
        if (controller.get_digital(DIGITAL_L1)){
            if(intaking){
                intaking = false;
            } else {
                intaking = true;
                spitting = false;
            } 
            pros::delay(200);
        } else if (controller.get_digital(DIGITAL_L2)){
            if(spitting){
                spitting = false;
            } else {
                intaking = false;
                spitting = true;
            }
            pros::delay(200);
        }

        if (controller.get_digital(DIGITAL_R1)){
            spinMotor.move_absolute(spot, 127);
            spinMotor.set_zero_position(0);
            spot = -spot;
            pros::delay(200);
        }

        //move the intake and the conveyor
        if (intaking){
            intakeMotor.move(127);
            conveyorMotor.move(127);
        } else if (spitting){
            intakeMotor.move(-127);
            conveyorMotor.move(-127);
        } else {
            intakeMotor.move(0);
            conveyorMotor.move(0);
        }


        
        // delay to save resources
        pros::delay(10);
    }
}