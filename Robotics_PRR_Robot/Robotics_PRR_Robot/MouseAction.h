#pragma once

class MouseAction {
public:
	int x;
	int y;
	int button;
	int state;
	MouseAction(int x, int y, int button, int state);
};
