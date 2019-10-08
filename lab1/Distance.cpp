#include "Distance.h"
#include <math.h>
double distance(Point& A, Point& B) {
	double X = B.x - A.x;
	double Y = B.y - A.y;
	return sqrt(X*X + Y*Y);
}