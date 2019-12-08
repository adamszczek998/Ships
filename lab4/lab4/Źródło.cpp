#include "BusTime.h"
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <queue>
#include <vector>
#include <functional>
#include <map>
#include <fstream>
#include <unordered_map>

struct BusTime{
	int godzina;
	int minuta;

	 BusTime(std::string czas) {
		std::string godzinaS="  ";
		std::string minutaS="  ";

		godzinaS[0] = czas[0];
		godzinaS[1] = czas[1];

		minutaS[0] = czas[3];
		minutaS[1] = czas[4];

		std::stringstream geekG(godzinaS);
		geekG >> godzina;
		std::stringstream geekM(minutaS);
		geekM >> minuta;
	}

	std::string ToString() const {
		std::string czasBackToString;
		
		if (godzina < 10) czasBackToString = "0" + std::to_string(godzina) + ":";
		else czasBackToString = std::to_string(godzina) + ":";
		if (minuta < 10) czasBackToString += "0" + std::to_string(minuta);
		else czasBackToString += std::to_string(minuta);
		return czasBackToString;
	}

	bool operator<(const BusTime& godzinaMinuta) const {
		if (godzina != godzinaMinuta.godzina) return godzina > godzinaMinuta.godzina;
		else return minuta > godzinaMinuta.minuta;
	}

};

struct BusLine {
public:
	std::priority_queue<BusTime> kolejka;
};
struct BusStop {
	std::map<int, BusLine> linia;
};


void print_queue(BusLine& q) {
	while (!q.kolejka.empty()) {
		std::cout << (q.kolejka.top()).ToString() << "\n";
		q.kolejka.pop();
	}
	std::cout << '\n';
}

void PrepareBusBoard(const std::string& file_name);

int main() {

	//BusTime czasBusa("03:05");
	//std::cout << czasBusa.godzina << ":" << czasBusa.minuta << std::endl;
	//std::cout<<czasBusa.ToString();
	BusTime test1("12:33");
	BusTime test2("02:33");
	BusTime test3("12:55");
	std::cout << "\n\n";
	BusLine kolejka;
	kolejka.kolejka.push(test1);
	kolejka.kolejka.push(test2);
	kolejka.kolejka.push(test3);
	
	print_queue(kolejka);

	PrepareBusBoard("lista.txt");

	return 0;
}

void PrepareBusBoard(const std::string& file_name) {
	std::ifstream input(file_name);
	if (input.is_open()) {
		//std::unordered_map<BusLine, BusStop>::iterator LiniaAutobusowa;
		std::vector<BusLine> LiniaAutobusowa(4);
		std::string bufor;
		int i=-1;
		while (!input.eof()) {
			getline(input, bufor);
			if ((int)bufor[0] > '9') {
				++i;
			}
			LiniaAutobusowa[i].kolejka.push(bufor);

		}
	   		 	 
		input.close();
	}
}



