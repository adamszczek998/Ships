#pragma once
#include <math.h>

class Point {

public:
	double x;
	double y;
	inline Point(double x, double y) : x(x), y(y) {}
};

inline double distance(const Point& A, const Point& B) {
	double X = B.x - A.x;
	double Y = B.y - A.y;
	return sqrt(X*X + Y*Y);
}