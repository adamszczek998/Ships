#pragma once
#include <iostream>

class Vector2D {
private:
	float x, y;
public:
	Vector2D() { x = y = 0; }
	Vector2D(float x, float y) : x(x), y(y){}
	
	Vector2D operator=(const Vector2D& other) { //przypisanie
		x = other.x;
		y = other.y;
		return *this;	
	}
	Vector2D& operator--() {//pre
		x -= 1.0;
		y -= 1.0;
		return *this;
	}
	Vector2D operator--(int) {//post
		Vector2D copy(*this);
		x -= 1.0;
		y -= 1.0;
		return copy;
	}
	float& operator[](int a) {//index
		if (a == 0) { return x; }
		else { return y; }
	}
	Vector2D& operator+=(const Vector2D& a) {
		x = x + a.x;
		y = y + a.y;
		return *this;
	}
	Vector2D operator*(float a) {//mnozenie skalarne
		Vector2D b(*this);
		b.x = x * a;
		b.y = y * a;
		return b;
	}

	void normalise() {
		float odleglosc = sqrt(x*x+y*y);
		this->x = x / odleglosc;
		this->y = y / odleglosc;
	}

	void Show() {
		std::cout << x << " " << y << std::endl;
	}




};