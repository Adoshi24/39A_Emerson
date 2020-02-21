#include "main.h"

void setDrive(int left, int right){
  driveLB = left;
  driveLF = left;
  driveRF = right;
  driveRB = right;
}
void setDriveMotors(){
  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  if (abs(leftJoystick)<10){
    leftJoystick = 0;
  }
  if (abs(rightJoystick)<10){
    rightJoystick = 0;
  }
  setDrive(leftJoystick, rightJoystick);
}

void resetDriveEncoders(){
  driveLB.tare_position();
  driveLF.tare_position();
  driveRF.tare_position();
  driveRB.tare_position();
}

double avgDriveEncoderValue(){
  return (fabs(driveLB.get_position()) +
            fabs(driveLF.get_position()) +
            fabs(driveRF.get_position()) +
            fabs(driveRB.get_position()))/4;
}

void translate(int units, int voltage){
  int direction = abs(units) / units; //1 or -1 based on units provided
  resetDriveEncoders();
  while(fabs(avgDriveEncoderValue()) < abs(units)) {
    setDrive(voltage * direction, voltage * direction);
    pros::delay(10);
  }
  //brake
  setDrive(-10 * direction, -10 * direction);
  pros::delay(200);
  //set back to coast
  setDrive(0,0);
}

void steerTime(int left, int right, int time){
  int counterLeft = abs(left)/left;
  int counterRight = abs(right)/right;
  setDrive(left,right);
  pros::delay(time);
  setDrive(-10 * counterLeft, -10 * counterRight);
  pros::delay(250);
  setDrive(0,0);
}
