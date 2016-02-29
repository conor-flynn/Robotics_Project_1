#include "Graphics.h"

Graphics::Graphics(int argc, char ** argv, int width, int height, int start_x, int start_y, const char * window_name) {

	screen_width = width;
	screen_height = height;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(start_x, start_y);

	glutCreateWindow(window_name);
}






void Graphics::writeText(void* font, char* text, float x, float y) {
	glRasterPos2f(x, y);
	while (*text != '\0') {
		glutBitmapCharacter(font, *text);
		++text;
	}
}

void Graphics::drawButton(Button * b) {

	// Draws a button 'b' and writes the necessary text of the button

	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex2f(b->x, b->y);
	glVertex2f(b->x, b->y + b->h);
	glVertex2f(b->x + b->w, b->y + b->h);
	glVertex2f(b->x + b->w, b->y);
	glEnd();

	float text_length = ( (float) glutBitmapLength(GLUT_BITMAP_HELVETICA_10, reinterpret_cast<const unsigned char*>(b->label)) / screen_width)*2;
	float x_offset = (button_width - text_length) / 2.0f;
	float xx = b->x + x_offset;
	float yy = b->y + (button_height / 2.0f) - 0.01f;

	glColor3f(0.1f, 0.1f, 0.1f);
	writeText(GLUT_BITMAP_HELVETICA_10, b->label, xx, yy);
}

void Graphics::drawButtons(vector<Button*> buttons) {
	for (Button* button : buttons) {
		drawButton(button);
	}
}

void Graphics::positionButtons(vector<Button*> buttons) {

	// This determines the x and y coordinates of each of the buttons so that they can be accurately drawn to the screen

	float x		= -1 + outer_spacing + inner_spacing;
	float y0	= -1 + outer_spacing + inner_spacing;
	float y1	= y0 + inner_spacing + button_height;
	float y2	= y0 + inner_spacing + (button_height / 2.0f);

	for (Button* button : buttons) {

		button->x = x + (inner_spacing + button_width) * button->x;;

		if (button->y == 0) {
			button->y = y0;
		}
		else if (button->y == 1) {
			button->y = y1;
		}
		else {
			button->y = y2;
		}
		button->w = button_width;
		button->h = button_height;
	}
}

void Graphics::drawBackground() {
	glClearColor(0, 0, 0, 0);	

	// Primary draw-space (where the robot will be drawn)
	glBegin(GL_POLYGON);
	glColor3f(0.95f, 0.95f, 0.95f);
	glVertex2f(-1 + outer_spacing,		-1 + outer_spacing + outer_spacing + secondary_width);
	glVertex2f(-1 + outer_spacing,		 1 - outer_spacing);
	glVertex2f(1 - outer_spacing,		 1 - outer_spacing);
	glVertex2f(1 - outer_spacing,		-1 + outer_spacing + outer_spacing + secondary_width);
	glEnd();

	// Secondary draw-space (where the buttons will be drawn)
	glBegin(GL_POLYGON);
	glColor3f(0.95f, 0.95f, 0.95f);
	glVertex2f(-1 + outer_spacing,		-1 + outer_spacing);
	glVertex2f(-1 + outer_spacing,		-1 + outer_spacing + secondary_width);
	glVertex2f(1 - outer_spacing,		-1 + outer_spacing + secondary_width);
	glVertex2f(1 - outer_spacing,		-1 + outer_spacing);
	glEnd();
}

void Graphics::recalculatePoints(float* data) {
	// Max reach = 325
	float x_offset = 0;
	float y_offset = 1 - primary_width + outer_spacing;

	for (int i = 0; i < 8; i++) {
		data[i] = data[i] / screen_width;
		if (i % 2 == 0) {
			// x_coordinate
			data[i] = data[i] + x_offset;
		}
		else {
			// y_coordinate
			data[i] = data[i] + y_offset;
		}
	}
}

void Graphics::drawRobot(float* data) {
	recalculatePoints(data);

	float line_width = 2.5f;
	float color[3] = { 0.5f, 0.5f, 0.5f };

	glLineWidth(line_width);
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINES);
	glVertex2f(data[0], data[1]);
	glVertex2f(data[2], data[3]);
	glEnd();

	glLineWidth(line_width);
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINES);
	glVertex2f(data[2], data[3]);
	glVertex2f(data[4], data[5]);
	glEnd();

	glLineWidth(line_width);
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINES);
	glVertex2f(data[4], data[5]);
	glVertex2f(data[6], data[7]);
	glEnd();
}

void Graphics::addPaint(float x, float y) {
	x = x / screen_width;
	y = y / screen_width;
	paint_locations.push_back(x);
	paint_locations.push_back(y);
}

struct Point {
	float x;
	float y;
	Point(float xx, float yy) {
		x = xx;
		y = yy;
	}
	void normalize() {
		float magnitude = sqrt( (x*x) + (y*y) );
		if (magnitude == 0) return;
		x = x / magnitude;
		y = y / magnitude;
	}
	Point pixelate(float radius, float reduction) {
		x *= radius / reduction;
		y *= radius / reduction;
		return *this;
	}
	Point offset(float xx, float yy) {
		x += xx;
		y += yy;
		return *this;
	}
};

Point rotate(float x, float y, float angle) {
	float xx = x;
	float yy = y;

	x = (xx * cos(angle)) - (yy * sin(angle));
	y = (xx * sin(angle)) + (yy * cos(angle));
	Point p = Point(x, y);
	p.normalize();
	return p;
}

void Graphics::drawPaint() {
	float radius = 5.0f;
	for (int i = 0; i < paint_locations.size(); i += 2) {
		float x_offset = paint_locations[i];
		float y_offset = paint_locations[i + 1] - outer_spacing;

		float x = 0;
		float y = 1;

		for (float angle = 0; angle < 180; angle++) {
			Point x0 = rotate(x, y, angle).pixelate(radius, screen_width).offset(x_offset, y_offset);
			Point x1 = rotate(x, y, angle + 90).pixelate(radius, screen_width).offset(x_offset, y_offset);
			Point x2 = rotate(x, y, angle + 180).pixelate(radius, screen_width).offset(x_offset, y_offset);

			glColor3f(0.5f, 0.5f, 0.5f);
			glBegin(GL_TRIANGLES);
			glVertex2f(x0.x, x0.y);
			glVertex2f(x1.x, x1.y);
			glVertex2f(x2.x, x2.y);
			glEnd();
		}
	}
}