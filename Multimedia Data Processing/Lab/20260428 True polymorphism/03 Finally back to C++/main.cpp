#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

#include "canvas.hpp"
#include "string.h"

struct shape {
	int x_, y_;
	char c_;

	shape(int x, int y, char c) : x_(x), y_(y), c_(c) {}
	// virtual ~shape() {}
	virtual ~shape() = default;	 // This is written in order to enforce the fact
								 // that it's virtual

	// Every child object needs to implement this function. This is called a
	// pure virtual function (and the class is now called an abstract class)
	virtual void draw(canvas& c) const = 0;
};

struct rectangle : public shape {
	int x2_, y2_;

	rectangle(int x1, int y1, int x2, int y2, char c)
		: shape(x1, y1, c), x2_(x2), y2_(y2) {}
	~rectangle() { std::cout << "Deleting `rectangle`\n"; }

	void draw(canvas& c) const override { c.rectangle(x_, y_, x2_, y2_, c_); }
};

struct point : public shape {
	point(int x, int y, char c) : shape(x, y, c) {}
	~point() { std::cout << "Deleting `point`\n"; }

	void draw(canvas& c) const override { c.set(x_, y_, c_); }
};

struct circle : public shape {
	int r_;

	circle(int x, int y, int r, char c) : shape(x, y, c), r_(r) {}
	~circle() { std::cout << "Deleting `circle`\n"; }

	void draw(canvas& c) const override { c.circle(x_, y_, r_, c_); }
};

struct line : public shape {
	int x2_, y2_;

	line(int x1, int y1, int x2, int y2, char c)
		: shape(x1, y1, c), x2_(x2), y2_(y2) {}
	~line() { std::cout << "Deleting `line`\n"; }

	void draw(canvas& c) const override { c.line(x_, y_, x2_, y2_, c_); }
};

int main(void) {
	canvas c(80, 25);

	/*
	rectangle 0 0 79 24 *
	point 5 15 ?
	circle 10 10 4 @
	circle 70 10 4 @
	line 40 15 40 20 |
	*/

	std::vector<shape*> shapes;
	shapes.push_back(new rectangle(0, 0, 79, 24, '*'));
	shapes.push_back(new point(5, 15, '?'));
	shapes.push_back(new circle(10, 10, 4, '@'));
	shapes.push_back(new circle(70, 10, 4, '@'));
	shapes.push_back(new line(40, 15, 40, 20, '|'));

	for (size_t i = 0; i < shapes.size(); ++i) {
		shapes[i]->draw(c);
	}
	c.out(std::cout);

	for (size_t i = 0; i < shapes.size(); i++) {
		delete shapes[i];
	}

	return 0;
}
