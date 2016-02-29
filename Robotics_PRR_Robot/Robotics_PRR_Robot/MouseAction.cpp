#include "stdafx.h"
#include "MouseAction.h"


MouseAction::MouseAction(int x, int y, int button, int state) {
	this->x = x;
	this->y = y;
	this->button = button;
	this->state = state;
}