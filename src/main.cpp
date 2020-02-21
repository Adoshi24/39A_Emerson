#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);

	driveLB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveLF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRF.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	driveRB.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	tray.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intakeL.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	intakeR.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
int steerTimeReduce = 700;
void deploy(){
	autonMoveTrayDriveForward(1500, 127); //
	autonMoveTray(1380, 127);
	autonMoveTray(600,40);
	pros::delay(500);
	autonMoveTray(-2000, 127);
	activateIntake(-30);
	steerTime(-50,-50,1000);
	activateIntake(0);
}

void flipOutTray(){
	autonMoveArm(127, 400);
	autonMoveArm(-127, 400);
}

void grabInitialRow(){ //remember to turn off intake
	activateIntake(127);//activateIntake(int voltage)
	pros::delay(300);
	translate(3200, 60); //translate(ticks,voltage)
}

void redSquareFive(){ //x = 1
	grabInitialRow();
	translate(-500, 90);
	activateIntake(0);
	translate(-1400, 90);
	steerTime(50,-50,1400);
	steerTime(70,70,1600-steerTimeReduce);//go forward , was 1600 ms without mtdf command
	deploy();
}
void redSquareEight(){ //2
	grabInitialRow();
	steerTime(50, -50, 300);
	translate(-2500, 70);
	steerTime(40, 80, 1000);
	translate(2000, 60);
	steerTime(50, -50, 1500);
	steerTime(70, 70, 4000-steerTimeReduce);
	deploy();
}
void redRectangleTwo(){
	activateIntake(127);
	translate(1200,80);
	activateIntake(0);
	steerTime(-50, 50, 1400);
	steerTime(70, 70, 1000-steerTimeReduce);
	deploy();
}
void redRectangleFive(){ //3
	activateIntake(127);
	translate(1500,80);
	activateIntake(0);
	translate(1500,80);
	activateIntake(127);
	translate(500,80);
	translate(-2500, 60);
	steerTime(50, -50, 1000);
	translate(3000,80);
	activateIntake(0);
	translate(-3000, 80);
	steerTime(50, -50, 1500);
	steerTime(70, 70, 1000-steerTimeReduce);
	deploy();
}
void blueSquareFive(){ //4
	translate(-500, 90);
	activateIntake(0);
	translate(-1400, 90);
	steerTime(-50,50,1400);
	steerTime(70,70,1600 - steerTimeReduce);//go forward
	deploy();
}
void blueSquareEight(){ //5
	grabInitialRow();
}
void blueRectangleTwo(){

}
void blueRectangleFive(){ //6

}
void autonomous() {
	int x = 1; //selects which auton to run
	flipOutTray();
	if (x==1){
		redSquareFive();
	}
	else if (x==2){
		redSquareEight();
	}
	else if (x==3){
		redRectangleTwo();
	}
	else if (x==4){
		redRectangleFive();
	}
	else if (x==5){
		blueSquareFive();
	}
	else if (x==6){
		blueSquareEight();
	}
	else if (x==7){
		blueRectangleTwo();
	}
	else {
		blueRectangleFive();
	}

}
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while(true){
		setDriveMotors();
		moveArm();
		moveTray();
		moveArmTray();
		moveIntake();
		pros::delay(10);
	}
}
