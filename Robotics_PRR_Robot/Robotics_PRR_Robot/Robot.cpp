#include "Robot.h"

Robot::Robot() {

	joint0x = 0;
	joint0y = 0;

	joint1x = 0;
	joint1y = 150;

	joint2x = 0;
	joint2y = 250;

	paintx  = 0;
	painty  = 325;
}

// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~

// Testing values to make sure the robot can be drawn with updated values
void Robot::joint0Adjust(float amount) {
	joint0x += amount;
	paintx -= amount;
	painty += (amount / 2);
}
void Robot::joint1Adjust(float amount) {
	joint1x += amount;
	joint1y -= amount;
}
void Robot::joint2Adjust(float amount) {
	joint2x -= amount;
	joint2y += amount;
}