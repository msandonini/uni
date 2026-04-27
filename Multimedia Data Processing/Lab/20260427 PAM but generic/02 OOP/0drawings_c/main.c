#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>

#include "canvas.h"
#include "string.h"

/*
type_of_object parameter_1 parameter_2 ... parameter_n

rectangle 0 0 79 24 *
point 5 15 ?
circle 10 10 4 @
circle 70 10 4 @
line 40 15 40 20 |
*/

// STEP 1: Create the shape object for drawing

typedef struct shape {
	int x_, y_;
	char c_;
} shape;

shape* shape_create(shape* this, int x, int y, char c) {
	this->x_ = x;
	this->y_ = y;
	this->c_ = c;

	return this;
}
shape* shape_destroy(shape* this) { return this; }
shape* new_shape(shape* this, int x, int y, char c) {
	return shape_create(malloc(sizeof(shape)), x, y, c);
}
void delete_canvas(shape* this) { free(shape_destroy(this)); }
// END STEP 1

// STEP 2: Write an interface to write a shape
void shape_draw(const shape* this, canvas* c) {
	canvas_set(c, this->x_, this->y_, this->c_);
}
// END STEP 2

// STEP 3: Create a rectangle based on a shape (inheritance-like behaviour)
typedef struct rectangle {
	shape base_;

	int x2_, y2_;
} rectangle;

rectangle* rectangle_create(rectangle* this, int x, int y, int x2, int y2,
							char c) {
	shape_create(&this->base_, x, y, c);

	this->x2_ = x2;
	this->y2_ = y2;

	return this;
}
rectangle* rectangle_destroy(rectangle* this) {
	shape_destroy(&this->base_);
	return this;
}
rectangle* new_rectangle(rectangle* this, int x, int y, int x2, int y2,
						 char c) {
	return rectangle_create(malloc(sizeof(rectangle)), x, y, x2, y2, c);
}
void delete_canvas(rectangle* this) { free(rectangle_destroy(this)); }
void rectangle_draw(const rectangle* this, canvas* c) {
	canvas_rectangle(c, this->base_.x_, this->base_.y_, this->x2_, this->y2_,
					 this->base_.c_);
}
// END STEP 3

void draw_file(FILE* f, canvas* c) {
	char type[30];
	while (fscanf(f, "%29s", type) == 1) {
		if (strcmp(type, "point") == 0) {
			int x, y;
			char ch;
			fscanf(f, "%d%d %c", &x, &y, &ch);
			canvas_set(c, x, y, ch);
		} else if (strcmp(type, "line") == 0) {
			int x0, y0, x1, y1;
			char ch;
			fscanf(f, "%d%d%d%d %c", &x0, &y0, &x1, &y1, &ch);
			canvas_line(c, x0, y0, x1, y1, ch);
		} else if (strcmp(type, "rectangle") == 0) {
			int x0, y0, x1, y1;
			char ch;
			fscanf(f, "%d%d%d%d %c", &x0, &y0, &x1, &y1, &ch);
			canvas_rectangle(c, x0, y0, x1, y1, ch);
		} else if (strcmp(type, "circle") == 0) {
			int xm, ym, r;
			char ch;
			fscanf(f, "%d%d%d %c", &xm, &ym, &r, &ch);
			canvas_circle(c, xm, ym, r, ch);
		}
	}
}

int main(void) {
	canvas* c = new_canvas(80, 25);

	rectangle r;
	rectangle_create(&r, 0, 0, 79, 24, '*');
	rectangle_draw(&r, c);

	draw_file(stdin, c);

	canvas_out(c, stdout);
	delete_canvas(c);
}