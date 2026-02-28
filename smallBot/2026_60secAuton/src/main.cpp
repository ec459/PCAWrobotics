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
    chassis.moveToPoint(0, -50, 10000,{.forwards = false, .maxSpeed = 60} );
    chassis.moveToPoint(0, 0, 10000,{.forwards = true, .maxSpeed = 60} );
    chassis.moveToPoint(0, -100, 10000,{.forwards = false, .maxSpeed = 100} );
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
    spinMotor.move_absolute(spot, 127);
    spinMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


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

        //spin motor buttons
        //if (controller.get_digital(DIGITAL_R1)){
          //  if(!turnning){
            //    turnning = true;
                
              //  pros::lcd::print(1,"Go!!!",spinMotor.get_position());
                //pros::delay(200);
            //} 
        //} else if (controller.get_digital(DIGITAL_R2)){
          //  if(turnning){
            //    turnning = false;
              //  pros::lcd::print(1,"The stop button was clicked",spinMotor.get_position());
                //pros::delay(200);
            //}
        //}

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

        //move the spinner
       // if (turnning){
          //  if (spinMotor.get_position() >=-5 && spinMotor.get_position() <=10){
            //    spot = 450;
            //} else if (spinMotor.get_position() >=450 && spinMotor.get_position() <=475){
              //  spot = 0;
            //}
            //spinMotor.move_absolute(spot, 127);

            // pros::lcd::print(3,"This should be spinning %d",spinMotor.get_position());
            //spinMotor.move_absolute(400, 127);
             //pros::lcd::print(3,"This should be spinning %d",spinMotor.get_position());
             //pros::delay(500);
            //spinMotor.move_absolute(0, 127);
             //pros::delay(500);
             //pros::lcd::print(3,"This should be spinning %d",spinMotor.get_position());


        //} else {
          //  spinMotor.move(0);
            
        //pros::lcd::print(3,"This should not be spinning",spinMotor.get_position());
        //}


        
        // delay to save resources
        pros::delay(10);
    }
}