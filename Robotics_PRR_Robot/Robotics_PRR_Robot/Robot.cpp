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
void Robot::joint0Slide(float amount) {
	joint0x += amount;
	joint1x += amount;
	joint2x += amount;
	paintx += amount;
}

void Robot::joint1CCW(float amount) {
	float radians = (amount*M_PI) / 180;
	float sn = sin(radians);
	float cs = cos(radians);
	joint2x = joint2x - joint1x;
	joint2y = joint2y - joint1y;
	float xx = joint2x*cs - joint2y*sn;
	float yy = joint2x*sn + joint2y*cs;
	joint2x = xx + joint1x;
	joint2y = yy + joint1y;

	//correct distance, wrong postion of last link when rotating middle one
	/* 
	float doubleradians = ((amount + amount)*M_PI) / 180;
	float snd = sin(doubleradians);
	float csd = cos(doubleradians);
	paintx = paintx - joint2x;
	painty = painty - joint2y;
	xx = paintx*snd - painty*csd;
	yy = paintx*csd + painty*snd;
	paintx = xx + joint2x;
	painty = yy + joint2y;
	*/
	
	float doubleradians = ((amount+amount)*M_PI) / 180;
	float snd = sin(doubleradians);
	float csd = cos(doubleradians);
	paintx = paintx - joint2x;
	painty = painty - joint2y;
	xx = paintx*csd - painty*snd;
	yy = paintx*snd + painty*csd;
	paintx = xx + joint2x;
	painty = yy + joint2y;
	
}

void Robot::joint1CC(float amount) {
	float radians = (amount*M_PI) / 180;
	float sn = sin(radians);
	float cs = cos(radians);
	joint2x = joint2x - joint1x;
	joint2y = joint2y - joint1y;
	float xx = joint2x*cs + joint2y*sn;
	float yy = -joint2x*sn + joint2y*cs;
	joint2x = xx + joint1x;
	joint2y = yy + joint1y;

	//correct distance, wrong postion of last link when rotating middle one
	/*
	float doubleradians = ((amount + amount)*M_PI) / 180;
	float snd = sin(doubleradians);
	float csd = cos(doubleradians);
	paintx = paintx - joint2x;
	painty = painty - joint2y;
	xx = paintx*snd + painty*csd;
	yy = -paintx*csd + painty*snd;
	paintx = xx + joint2x;
	painty = yy + joint2y;
	*/

	
	float doubleradians = ((amount+amount)*M_PI) / 180;
	float snd = sin(doubleradians);
	float csd = cos(doubleradians);
	paintx = paintx - joint2x;
	painty = painty - joint2y;
	xx = paintx*csd + painty*snd;
	yy = -paintx*snd + painty*csd;
	paintx = xx + joint2x;
	painty = yy + joint2y;
	
}

void Robot::joint2CCW(float amount) {
	float radians = (amount*M_PI) / 180;
	float sn = sin(radians);
	float cs = cos(radians);
	paintx = paintx - joint2x;
	painty = painty - joint2y;
	float xx = paintx*cs - painty*sn;
	float yy = paintx*sn + painty*cs;
	paintx = xx + joint2x;
	painty = yy + joint2y;
}

void Robot::joint2CC(float amount) {
	float radians = (amount*M_PI) / 180;
	float sn = sin(radians);
	float cs = cos(radians);
	paintx = paintx - joint2x;
	painty = painty - joint2y;
	float xx = paintx*cs + painty*sn;
	float yy = -paintx*sn + painty*cs;
	paintx = xx + joint2x;
	painty = yy + joint2y;
}