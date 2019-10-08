#pragma once
#include "Point.h"
#include <iostream>



class Circle {
private:
	Point srodek;
	double promien;

public:
	inline void set_promien(double promien) {
		this->promien = promien;
	}
	inline double get_promien() const {
		return promien;
	}
	inline void set_srodek(const Point& srodek) {
		this->srodek = srodek;
	}
	inline Point get_srodek() const {
		return srodek;
	}

	Circle(double promien, double x, double y);
	Circle(const Circle& kopia);

	double  area() const { return 2 * 3.14*promien*promien; }
	double permimeter() const { return 2 * 3.14*promien; }
	void print() const {
		std::cout << "x: " << srodek.x << " y: " << srodek.y << std::endl;
		std::cout << "Promien: " << promien;
	}
};

enum polozenie { rozlaczne_zewnetrznie, styczne_zew, przecinajace_sie, styczne_wew, rozlaczne_wew, wspolsrodkowe };

polozenie circlesLocation (const Circle& Aa, const Circle& Bb);

