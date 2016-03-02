#ifndef ROBOT_H
#define ROBOT_H

#define _USE_MATH_DEFINES
#include<stdlib.h>
#include<math.h>

using namespace std;

class Robot {
public:

	// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
	// =~=~=~  VARIABLES  ~=~=~=~=~=~=~=~
	// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~

	// The Interface class reads these values and sends them to the adjusting functions
	const float slide_amount = 5;
	const float rotate_amount = 5;

	// These values are in pixels
	float joint0x;
	float joint0y;

	float joint1x;
	float joint1y;

	float joint2x;
	float joint2y;

	float paintx;
	float painty;

	// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
	// =~=~=~  CONSTRUCTORS  =~=~=~=~=~=~
	// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~

	Robot();

	// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
	// =~=~=~  FUNCTIONS  ~=~=~=~=~=~=~=~
	// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~

	// Rather than have separate counter-clock-wise and clock-wise functions, they are combined into a single value
	// 'amount' is either +slide_amount or -slide_amount (the same for rotate_amount)
	void joint0Slide(float amount);
	void joint1CC(float amount);
	void joint1CCW(float amount);
	void joint2CC(float amount);
	void joint2CCW(float amount);

};

#endif