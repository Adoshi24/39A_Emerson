#include "main.h"

void moveArm(){
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    arm.move_velocity(100);
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    arm.move_velocity(-100);
    }
  else {
    arm.move_velocity(0);
  }
}

void moveArmTray(){
  if ((controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)||controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)
)&& (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)||controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))){
    moveArm();
    moveTray();
}
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)||controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
    moveTray();
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
    resetTrayEncoder();
    tray.move_absolute(1600,127);
    arm.move_velocity(100);
  }
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
    tray.move_velocity(-50);
    arm.move_velocity(-100);
  }
  else {
    tray.move_velocity(0);
    arm.move_velocity(0);
  }
}

void autonMoveArm(int voltage, int time){
  arm = voltage;
  pros::delay(time);
  arm = 0;
}

// // if (trayup||traydown && armup||armdown)
//moveArm()
//moveTray()
//else if (traydown){
// // run tray;
// else if (trayup){
// else if (arm up) move both
// else if arm down move both
//else if (
// }
// }
