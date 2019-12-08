#include <string>
#include "NumberSequence.h"

int main(){



	ArithmeticSequence ciagArytmetyczny(5,3);
	ArithmeticSequence ciagArytmetycznyKopia(ciagArytmetyczny);
	ArithmeticSequence ciagArytmetycznyPrzeniesiony(std::move(ciagArytmetyczny));


	GeometricSequence ciagGeometryczny(6, 4);
	GeometricSequence ciagGeometrycznyKopia(ciagGeometryczny);
	GeometricSequence ciagGeometrycznyPrzeniesiony(std::move(ciagGeometryczny));


	SequenceFactory* nowy("arithmetic 8 5");

	return 0;
}