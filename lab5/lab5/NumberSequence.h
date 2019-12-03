#pragma once
#include <string>
#include <sstream>
#include <iostream>

class NumberSequence {
private:
	std::string name;
public:
	
	virtual ~NumberSequence() {};
	//NumberSequence() {};//
	NumberSequence(const std::string &nazwa) : name(nazwa) {}
	NumberSequence(const NumberSequence &kopia) : name(kopia.name) {}
	NumberSequence(NumberSequence &&przenoszony) : name(std::move(przenoszony.name)) {}
	
	virtual double calc_nth(const int n) const =0;

	std::string to_string() const {
		std::string lancuch = name;
		for (int i = 1; i <= 10; ++i) {
			lancuch += " "+std::to_string(calc_nth(i));
		}
		return lancuch;
	}
};

class ArithmeticSequence :public NumberSequence {
private:
	double a1;
	double r;
public:
	ArithmeticSequence(const double a1, const double r) : a1(a1), r(r), NumberSequence("arithmetic") {}
	ArithmeticSequence(const ArithmeticSequence& kopia) : a1(kopia.a1), r(kopia.r), NumberSequence(kopia) {}
	ArithmeticSequence(ArithmeticSequence&& przenoszony) :a1(std::move(przenoszony.a1)), r(std::move(przenoszony.r)), NumberSequence(std::move(przenoszony)) {}

	double calc_nth(int n)const override { return a1 + (n - 1) * r; }
};

class GeometricSequence :public NumberSequence {
private:
	double a1;
	double q;
public:
	GeometricSequence(const double a1, const double q) : a1(a1), q(q), NumberSequence("geometric") {}
	GeometricSequence(const GeometricSequence& kopia) : a1(kopia.a1), q(kopia.q), NumberSequence(kopia) {}
	GeometricSequence(GeometricSequence&& przenoszony) : a1(przenoszony.a1), q(przenoszony.q), NumberSequence(std::move(przenoszony)) {}

	double calc_nth(int n)const override { return a1*pow(q,(n-1)); }
};

class SequenceFactory : NumberSequence {
private:

public:

	static NumberSequence* create( std::string& lancuch) {
		double a1;
		double rq;
		std::string nazwa;
		std::istringstream iss(lancuch);
		iss >> nazwa >> a1 >> rq;
		if (nazwa == "arithmetic") {
			return new ArithmeticSequence(a1, rq);
		}
		else if (nazwa == "geometric") {
			return new GeometricSequence(a1, rq);
		}
		else return nullptr;

 
	}
};