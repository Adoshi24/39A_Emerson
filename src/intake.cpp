#include "main.h"

void moveIntake(){
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
    intakeL.move_velocity(200);
    intakeR.move_velocity(200);
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
    intakeL.move_velocity(-200);
    intakeR.move_velocity(-200);
    }
  else {
    intakeL.move_velocity(0);
    intakeR.move_velocity(0);
  }
}

void runIntake(int voltage, int time){
  intakeL = voltage;
  intakeR = voltage;
  pros::delay(time);
  intakeL = 0;
  intakeR = 0;
  pros::delay(100);
}

void activateIntake(int voltage){
  intakeL = voltage;
  intakeR = voltage;
}
