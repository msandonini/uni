#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdlib.h>

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

/*
void draw_file(FILE *f, canvas *c)
{
	char type[30];
	while (fscanf(f, "%29s", type) == 1) {
		if (strcmp(type, "point") == 0) {
			int x, y;
			char ch;
			fscanf(f, "%d%d %c", &x, &y, &ch);
			canvas_set(c, x, y, ch);
*		}
		else if (strcmp(type, "line") == 0) {
			int x0, y0, x1, y1;
			char ch;
			fscanf(f, "%d%d%d%d %c", &x0, &y0, &x1, &y1, &ch);
			canvas_line(c, x0, y0, x1, y1, ch);
		}
		else if (strcmp(type, "rectangle") == 0) {
			int x0, y0, x1, y1;
			char ch;
			fscanf(f, "%d%d%d%d %c", &x0, &y0, &x1, &y1, &ch);
			canvas_rectangle(c, x0, y0, x1, y1, ch);
		}
		else if (strcmp(type, "circle") == 0) {
			int xm, ym, r;
			char ch;
			fscanf(f, "%d%d%d %c", &xm, &ym, &r, &ch);
			canvas_circle(c, xm, ym, r, ch);
		}
	}
}
*/

#define v(x) (void*)x

// STEP 1: Make everything generic
// The problem until now is that the shape object is not truly generic, so even
// if we know that rectangle, line, and point are shapes, for the code they are
// not. In order to solve this we can use pointers

typedef struct shape {
	int x_, y_;
	char c_;

	// This is a pointer to the draw function
	//(*draw)(const struct shape* this, canvas* c);
	(*draw)();	// We don't specify parameters so that compiler doesn't warn
				// about having different parameter types in the function
				// definition
	// In C++ this function pointer would be called a virtual function

	(*destroy)();
} shape;

void shape_draw(const shape* this, canvas* c) {
	canvas_set(c, this->x_, this->y_, this->c_);
}

shape* shape_destroy(shape* this) { return this; }
void shape_delete(shape* this) {
	this->destroy(this);
	free(this);
}

shape* shape_create(shape* this, int x, int y, char c) {
	this->x_ = x;
	this->y_ = y;
	this->c_ = c;
	this->draw = shape_draw;  // Here we assign the function
	this->destroy = shape_destroy;
	return this;
}
shape* new_shape(int x, int y, char c) {
	return shape_create(malloc(sizeof(shape)), x, y, c);
}

// This must be done for every "child" class
// After each class assigns its draw function we can use the generic "shape"
// object to interact with the specific object.
// This has the problem that each time I add a new functon I need to add a
// pointer to the struct, increasing its size, and each instance of this struct
// now has a pointer in it (SEE 02).

// END STEP 1

typedef struct rectangle {
	shape base;
	int x2_, y2_;
} rectangle;
rectangle* rectangle_destroy(rectangle* this) {
	shape_destroy(v(this));
	return this;
}
rectangle* new_rectangle(int x, int y, int x2, int y2, char c) {
	return rectangle_create(malloc(sizeof(rectangle)), x, y, x2, y2, c);
}
void delete_rectangle(rectangle* this) { free(rectangle_destroy(this)); }
void rectangle_draw(const rectangle* this, canvas* c) {
	canvas_rectangle(c, this->base.x_, this->base.y_, this->x2_, this->y2_,
					 this->base.c_);
}
rectangle* rectangle_create(rectangle* this, int x, int y, int x2, int y2,
							char c) {
	shape_create(v(this), x, y, c);
	this->x2_ = x2;
	this->y2_ = y2;
	this->base.draw = rectangle_draw;
	this->base.destroy = rectangle_destroy;
	return this;
}

typedef struct point {
	shape base;
} point;
point* point_destroy(point* this) {
	shape_destroy(v(this));
	return this;
}
point* new_point(int x, int y, char c) {
	return point_create(malloc(sizeof(point)), x, y, c);
}
void delete_point(point* this) { free(point_destroy(this)); }
void point_draw(const point* this, canvas* c) {
	canvas_set(c, this->base.x_, this->base.y_, this->base.c_);
}
point* point_create(point* this, int x, int y, char c) {
	shape_create(v(this), x, y, c);
	this->base.draw = point_draw;
	this->base.destroy = point_destroy;
	return this;
}

typedef struct circle {
	shape base;
	int r_;
} circle;
circle* circle_destroy(circle* this) {
	shape_destroy(v(this));
	return this;
}
circle* new_circle(int x, int y, int r, char c) {
	return circle_create(malloc(sizeof(circle)), x, y, r, c);
}
void delete_circle(circle* this) { free(circle_destroy(this)); }
void circle_draw(const circle* this, canvas* c) {
	canvas_circle(c, this->base.x_, this->base.y_, this->r_, this->base.c_);
}
circle* circle_create(circle* this, int x, int y, int r, char c) {
	shape_create(v(this), x, y, c);
	this->r_ = r;
	this->base.draw = circle_draw;
	this->base.destroy = circle_destroy;
	return this;
}

typedef struct line {
	shape base;
	int x1_, y1_;
} line;
line* line_destroy(line* this) {
	shape_destroy(v(this));
	return this;
}
line* new_line(int x, int y, int x1, int y1, char c) {
	return line_create(malloc(sizeof(line)), x, y, x1, y1, c);
}
void delete_line(line* this) { free(line_destroy(this)); }
void line_draw(const line* this, canvas* c) {
	canvas_line(c, this->base.x_, this->base.y_, this->x1_, this->y1_,
				this->base.c_);
}
line* line_create(line* this, int x, int y, int x1, int y1, char c) {
	shape_create(v(this), x, y, c);
	this->x1_ = x1;
	this->y1_ = y1;
	this->base.draw = line_draw;
	this->base.destroy = line_destroy;
	return this;
}

int main(void) {
	canvas* c = new_canvas(80, 25);

	// draw_file(stdin, c);

	/*
rectangle 0 0 79 24 *
point 5 15 ?
circle 10 10 4 @
circle 70 10 4 @
line 40 15 40 20 |
	*/
	rectangle* r1 = new_rectangle(0, 0, 79, 24, '*');
	point* p1 = new_point(5, 15, '?');
	circle* c1 = new_circle(10, 10, 4, '@');
	circle* c2 = new_circle(70, 10, 4, '@');
	line* l1 = new_line(40, 15, 40, 20, '|');

	int n = 5;
	shape** shapes = malloc(n * sizeof(shape*));
	shapes[0] = v(r1);
	shapes[1] = v(p1);
	shapes[2] = v(c1);
	shapes[3] = v(c2);
	shapes[4] = v(l1);

	rectangle_draw(v(shapes[0]), c);
	point_draw(v(shapes[1]), c);
	circle_draw(v(shapes[2]), c);
	circle_draw(v(shapes[3]), c);
	line_draw(v(shapes[4]), c);

	canvas_out(c, stdout);

	for (size_t i = 0; i < n; i++) {
		shapes[i]->destroy(v(shapes[i]));
	}

	delete_rectangle(r1);
	delete_point(p1);
	delete_circle(c1);
	delete_circle(c2);
	delete_line(l1);
	free(shapes);
	delete_canvas(c);
}