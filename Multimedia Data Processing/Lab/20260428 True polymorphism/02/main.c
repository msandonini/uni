#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdlib.h>

#include "canvas.h"
#include "string.h"

// STEP 1: Create the virtual function type

#define v(x) (void*)x

typedef void (*vfn)();
typedef struct shape {
	int x_, y_;
	char c_;

	vfn* vtbl;
} shape;

void shape_draw(const shape* this, canvas* c) {
	canvas_set(c, this->x_, this->y_, this->c_);
}

shape* shape_destroy(shape* this) { return this; }

// Here we define an array containing the functions
vfn shape_vtbl[] = {shape_draw, shape_destroy};

shape* shape_create(shape* this, int x, int y, char c) {
	this->x_ = x;
	this->y_ = y;
	this->c_ = c;
	this->vtbl = shape_vtbl;
	return this;
}
shape* new_shape(int x, int y, char c) {
	return shape_create(malloc(sizeof(shape)), x, y, c);
}
void shape_delete(shape* this) {
	this->vtbl[1](this);
	free(this);
}

// This again must be done for every "child" class.
// This is ugly, which is one of the reasons why they created a new language to
// manage it (C++)

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

vfn rectangle_vtbl[] = {rectangle_draw, rectangle_destroy};

rectangle* rectangle_create(rectangle* this, int x, int y, int x2, int y2,
							char c) {
	shape_create(v(this), x, y, c);
	this->x2_ = x2;
	this->y2_ = y2;
	this->base.vtbl = rectangle_vtbl;
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

vfn point_vtbl[] = {point_draw, point_destroy};

point* point_create(point* this, int x, int y, char c) {
	shape_create(v(this), x, y, c);
	this->base.vtbl = point_vtbl;
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

vfn circle_vtbl[] = {circle_draw, circle_destroy};

circle* circle_create(circle* this, int x, int y, int r, char c) {
	shape_create(v(this), x, y, c);
	this->r_ = r;
	this->base.vtbl = circle_vtbl;
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

vfn line_vtbl[] = {line_draw, line_destroy};

line* line_create(line* this, int x, int y, int x1, int y1, char c) {
	shape_create(v(this), x, y, c);
	this->x1_ = x1;
	this->y1_ = y1;
	this->base.vtbl = line_vtbl;
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
		shapes[i]->vtbl[1](shapes[i]);
	}

	free(shapes);
	delete_canvas(c);
}