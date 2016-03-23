#ifndef ROBOT_H
#define ROBOT_H


using namespace std;

class Robot {
public:

	// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
	// =~=~=~  VARIABLES  ~=~=~=~=~=~=~=~
	// =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~

	// The Interface class reads these values and sends them to the adjusting functions
	// These three values update on user input
	float joint_slide_amount;
	float joint_rotate_amount;
	float paint_slide_amount;

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
	void joint0Adjust(float amount);
	void joint1Adjust(float amount);
	void joint2Adjust(float amount);

	void paintBrushXAdjust(float amount);
	void paintBrushYAdjust(float amount);
	

};

#endif