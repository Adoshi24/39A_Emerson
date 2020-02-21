#include "main.h"

void moveTray(){
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
    tray.move_velocity(100);
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
    tray.move_velocity(-100);
    }
  else {
    tray.move_velocity(0);
  }
}

void resetTrayEncoder(){
  tray.tare_position();
}

void autonMoveTray (int units, int voltage){
  int direction = abs(units) / units;
  resetTrayEncoder();
  while(fabs(tray.get_position()) < abs(units)) {
    tray = voltage * direction;
    pros::delay(10);
  }
  tray = 0;
  pros::delay(100);
}

void autonMoveTrayDriveForward (int units, int voltage){
  int direction = abs(units) / units;
  resetTrayEncoder();
  while(fabs(tray.get_position()) < abs(units)) {
    tray = voltage * direction;
    setDrive(voltage/2,voltage/2);
    pros::delay(10);
  }
  tray = 0;
  pros::delay(100);
}

void trayP(int units, int voltage, double kp){
  int direction = abs(units)/units;
  resetTrayEncoder();
  while(fabs(tray.get_position()) < abs(units)) {
    double percentError = (units - tray.get_position())/units;
    int v = (int)(voltage * direction * kp * percentError);
    if (abs(v) > 127){
      tray = 127 * direction;
    }
    else {
      tray = v;
    }
    pros::delay(10);
  }
  tray = 0;
  pros::delay(100);
}
