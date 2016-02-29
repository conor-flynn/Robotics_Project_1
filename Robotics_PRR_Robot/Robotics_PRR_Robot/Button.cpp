#include "stdafx.h"
#include "Button.h"


Button::Button(float x, float y, float w, float h, char* label, ButtonCallback onClick) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->label = label;
	this->onClick = onClick;
}
