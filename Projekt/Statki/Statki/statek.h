#pragma once
#include <iostream>
#include <string>



struct Punkt {
	char y;
	short x;
};

enum Kierunek { polnoc, wschod, poludnie, zachod };
class Statek {
	private:
		short punktyZycia;
		short liczbaDostepnychStatkowDoRozstawienia;
		short dlugoscStatku;
		
	public:
		Kierunek kierunek;
		Punkt pozycjaRufy;
		//dekrementuje HP
		void trafienie() {
			punktyZycia--;
		}
		//dekrementuje pozosta�� liczb� statk�w do rozstawienia
		void rozstawiony() {
			liczbaDostepnychStatkowDoRozstawienia--;
		}
		//ustawia d�ugo�� statku
		Statek(short dlugosc) {
			dlugoscStatku = dlugosc;
		}
		//ustawia pozycj� rufy na planszy
		void setPozycjaRufy(Punkt pozycja) {
			pozycjaRufy = pozycja;
		}
		//ustawia kierunek statku
		void setKierunek(Kierunek podanyKierunek) {
			kierunek = podanyKierunek;
		}
		

};