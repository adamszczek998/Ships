#pragma once
#include <iostream>
#include <string>



struct Punkt {
	char y;
	short x;
};

class Statek {
	private:
		short punktyZycia;
		short liczbaDostepnychStatkowDoRozstawienia;
		short dlugoscStatku;
		Punkt pozycjaRufy;
		enum Kierunek { polnoc, wschod, poludnie, zachod };
		Kierunek kierunek;
	public:
		//dekrementuje HP
		void trafienie() {
			punktyZycia--;
		}
		//dekrementuje pozosta³¹ liczbê statków do rozstawienia
		void rozstawiony() {
			liczbaDostepnychStatkowDoRozstawienia--;
		}
		//ustawia d³ugoœæ statku
		Statek(short dlugosc) {
			dlugoscStatku = dlugosc;
		}
		//ustawia pozycjê rufy na planszy
		void setPozycjaRufy(Punkt pozycja) {
			pozycjaRufy = pozycja;
		}
		//ustawia kierunek statku
		void setKierunek(Kierunek podanyKierunek) {
			kierunek = podanyKierunek;
		}
		

};