#include "lemlib/api.hpp" // IWYU pragma: keep

#ifndef robotConfig_H
#define robotConfig_H

// controller
extern pros::Controller controller;

// motor groups (wheel motors connected together)
extern pros::MotorGroup leftMotors; // left motor group 
extern pros::MotorGroup rightMotors; // right motor group 

//sensors
// Inertial Sensor on port 10
extern pros::Imu imu;

// Motors
//singular motors ex:intake for botton
extern pros ::Motor intakeMotor;
extern pros::Motor conveyorMotor;
extern pros::Motor spinMotor;

// drivetrain settings
extern lemlib::Drivetrain drivetrain;

// lateral motion controller
extern lemlib::ControllerSettings linearController;

// angular motion controller
extern lemlib::ControllerSettings angularController;

// sensors for odometry
extern lemlib::OdomSensors sensors;

// input curve for throttle input during driver control
extern lemlib::ExpoDriveCurve throttleCurve;

// input curve for steer input during driver control
extern lemlib::ExpoDriveCurve steerCurve;

// create the chassis
extern lemlib::Chassis chassis;

#endif