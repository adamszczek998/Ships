#include "Circle.h"

Circle::Circle(const Circle& kopia) : promien(kopia.promien), srodek(kopia.srodek) {}
Circle::Circle(double promien, double x, double y) : promien(promien), srodek(x, y) {}