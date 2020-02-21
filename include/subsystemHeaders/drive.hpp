#include "main.h"

//drive helper functions
void setDrive(int left, int right);
//drive control functions
void setDriveMotors();

void resetDriveEncoders();

double avgDriveEncoderValue();

void translate(int units, int voltage);

void steerTime(int left, int right, int time);
