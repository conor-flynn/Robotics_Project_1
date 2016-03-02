#include "Interface.h"

Interface* Interface::s_instance;
Interface* Interface::getInstance() {
	return s_instance;
}
Interface* Interface::getInstance(int argc, char** argv) {
	if (s_instance == NULL) {
		s_instance = new Interface(argc, argv);
	}
	return s_instance;
}

Interface::Interface(int argc, char** argv) {

	const char* window_name = "Project 1";

	robot = new Robot();
	graphics = new Graphics(argc, argv, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_START_X, WINDOW_START_Y, window_name);


	// For initialization: 0, 0, 1, 1
		// means column 0, row 0, normal width, normal height
	// 3, 0.5f, 1, 1
		// means column 3, row 0.5, normal width, normal height
	// This initialization is then transformed into proper screen position in 'positionButtons()'

	// Slider
	buttons.push_back(new Button(0, 0, 1, 1, "Slide left", joint0SlideLeft));
	buttons.push_back(new Button(0, 1, 1, 1, "Slide right",joint0SlideRight));
	// Joint 1
	buttons.push_back(new Button(1, 0, 1, 1, "CCW", joint1CCW));
	buttons.push_back(new Button(1, 1, 1, 1, "CW", joint1CW));
	// Joint 2
	buttons.push_back(new Button(2, 0, 1, 1, "CCW", joint2CCW));
	buttons.push_back(new Button(2, 1, 1, 1, "CW", joint2CW));
	// Paint
	buttons.push_back(new Button(3, 0.5f, 1, 1, "Paint", paintAction));

	graphics->positionButtons(buttons);
}

Button* Interface::decodeMouse() {

	// For the current 'mouseAction', find out if a button has been pressed

	if (mouseAction == NULL) return NULL;
	if (mouseAction->state != GLUT_UP) return NULL;

	int x = mouseAction->x;
	int y = SCREEN_HEIGHT -mouseAction->y;

	for (auto &button : buttons) {
		float x0 = button->x;
		float x1 = button->x + button->w;
		float y0 = button->y;
		float y1 = button->y + button->h;

		x0 = ((x0 + 1) / 2.0f)*SCREEN_WIDTH;
		x1 = ((x1 + 1) / 2.0f)*SCREEN_WIDTH;
		y0 = ((y0 + 1) / 2.0f)*SCREEN_HEIGHT;
		y1 = ((y1 + 1) / 2.0f)*SCREEN_HEIGHT;

		if (x0 <= x && x <= x1 && y0 <= y && y <= y1) {
			return button;
		}
	}

	return NULL;
}

void Interface::determineAction() {
	//  Based on the current MouseAction, apply changes to robot
	Button* targetButton = decodeMouse();
	if (targetButton != NULL) {
		targetButton->onClick();
	}
}

void Interface::update() {

	// Redraw the screen
	graphics->drawBackground();
	graphics->drawButtons(buttons);
	
	// Respond to user input
	determineAction();
	
}

void Interface::drawUpdate() {
	// Since the robot could be in a different position or orientation, we need to update these changes to the screen
	float data[8] = { robot->joint0x, robot->joint0y, robot->joint1x, robot->joint1y, robot->joint2x, robot->joint2y, robot->paintx, robot->painty };

	graphics->drawRobot(data);
	graphics->drawPaint();
}

void Interface::paintAction() {
	Interface::getInstance()->graphics->addPaint(Interface::getInstance()->robot->paintx, Interface::getInstance()->robot->painty);
}

void Interface::joint0SlideLeft() {
	Interface::getInstance()->robot->joint0Slide( -1 * Interface::getInstance()->robot->slide_amount);
}

void Interface::joint0SlideRight() {
	Interface::getInstance()->robot->joint0Slide(Interface::getInstance()->robot->slide_amount);
}

void Interface::joint1CCW() {
	Interface::getInstance()->robot->joint1CCW(Interface::getInstance()->robot->rotate_amount);
}

void Interface::joint1CW() {
	Interface::getInstance()->robot->joint1CC(Interface::getInstance()->robot->rotate_amount);
}

void Interface::joint2CCW() {
	Interface::getInstance()->robot->joint2CCW(Interface::getInstance()->robot->rotate_amount);
}

void Interface::joint2CW() {
	Interface::getInstance()->robot->joint2CC(Interface::getInstance()->robot->rotate_amount);
}