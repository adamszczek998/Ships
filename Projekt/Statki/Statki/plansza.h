#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Punkt {
	int x;
	char y;
};

enum Kierunek { polnoc = 0, wschod = 1, poludnie = 2, zachod = 3 };//przenieść do klasy. Obecnie warningi

class Plansza : public sf::Drawable { //dziedziczenie po SFMLu
	private:
		sf::RectangleShape plansza;
		sf::Color kolorPlansza;
		char TabPlanszaGraczaLudzkiego[10][10] = {};//p-pusty, z-zajety, s-strzelany
		char TabPlanszaGraczaKomputerowego[10][10] = {};//p-pusty, z-zajety, s-strzelany

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(plansza);
		}
		
	public:
//KONSTRUKTORY==============================================================================================================================================================
		
		//Zainicjowanie planszy i ustawienie wszystkich pól jako pustych
		Plansza(sf::Vector2f size, sf::Vector2f position, sf::Color kolorPlansza) : kolorPlansza(kolorPlansza) {
			plansza.setSize(size);
			plansza.setPosition(position);
			plansza.setFillColor(kolorPlansza);
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) {
					TabPlanszaGraczaLudzkiego[j][i] = 'p';
					TabPlanszaGraczaKomputerowego[j][i] = 'p';
				}
			}
		}


//METODY==============================================================================================================================================================
		
		//Testowa funkcja wypisująca planszę w konsoli
		void wypiszPlansze() {
			//system("cls");
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) std::cout<<TabPlanszaGraczaLudzkiego[i][j]<<" ";
				std::cout << "\t";
				for (int j = 0; j < 10; ++j) std::cout << TabPlanszaGraczaKomputerowego[i][j] << " ";
				std::cout << "\n";
			}
		}
		
		
		//Funkcja sprawdzająca czy podane pola są wolne
		bool sprawdzCzyWolne(short dlugoscStatku, Punkt pozycjaRufy, Kierunek kierunek, bool gracz) {
			short i;
			//int* TabPlansza = &TabPlanszaGraczaLudzkiego;
			if (gracz == 0) {
				if (kierunek == polnoc) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if ((int)pozycjaRufy.y - 'A' - i < 0) return false;//Sprawdzanie czy gracz próbuje ustawić statek poza planszą
						if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' - i][pozycjaRufy.x] == 'z') return false;//Sprawdzanie bezpośrednio pól na których chcemy ustawić statek czy są puste
						if (pozycjaRufy.x - 1 >= 0) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' - i][pozycjaRufy.x - 1] == 'z') return false;//Sprawdzanie czy na polach po lewej nie ma statku
						if (pozycjaRufy.x + 1 <= 9) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' - i][pozycjaRufy.x + 1] == 'z') return false;//Sprawdzanie czy na polach po prawej nie ma statku
					}
					if ((int)pozycjaRufy.y - 'A' - (dlugoscStatku - 1) - 1 >= 0) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' - (dlugoscStatku - 1) - 1][pozycjaRufy.x] == 'z') return false;//Sprawdzanie pozycji nad statkiem czy nie jest zajęta przez inny statek
					if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' + 1][pozycjaRufy.x] == 'z') return false;//Sprawdzanie pozycji pod statkiem czy nie jest zajęta przez inny statek
				}
				else if (kierunek == poludnie) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if ((int)pozycjaRufy.y - 'A' + i > 10) return false;
						if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' + i][pozycjaRufy.x] == 'z') return false;
						if (pozycjaRufy.x - 1 >= 0) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' + i][pozycjaRufy.x - 1] == 'z') return false;//Sprawdzanie czy na polach po lewej nie ma statku
						if (pozycjaRufy.x + 1 <= 9) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' + i][pozycjaRufy.x + 1] == 'z') return false;//Sprawdzanie czy na polach po prawej nie ma statku
					}
					if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' - 1][pozycjaRufy.x] == 'z') return false;//Sprawdzanie pozycji nad statkiem czy nie jest zajęta przez inny statek
					if ((int)pozycjaRufy.y - 'A' + (dlugoscStatku - 1) + 1 <= 9) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' + (dlugoscStatku - 1) + 1][pozycjaRufy.x] == 'z') return false;//Sprawdzanie pozycji pod statkiem czy nie jest zajęta przez inny statek
				}
				else if (kierunek == wschod) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if (pozycjaRufy.x + i > 10) return false;
						if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x + i] == 'z') return false;
						if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' - 1][pozycjaRufy.x + i] == 'z') return false;//Sprawdzanie czy na polach nad nie ma statku
						if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' + 1][pozycjaRufy.x + i] == 'z') return false;//Sprawdzanie czy na polach pod nie ma statku
					}
					if (pozycjaRufy.x - 1 >= 0) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x - 1] == 'z') return false;//Sprawdzanie czy pozycja po lewej nie jest zajęta przez inny statek
					if (pozycjaRufy.x + (dlugoscStatku - 1) + 1 <= 9) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x + (dlugoscStatku - 1) + 1] == 'z') return false;//Sprawdzanie czy pozycja po prawej nie jest zajęta przez inny statek
				}
				else {//zachod
					for (i = 0; i < dlugoscStatku; ++i) {
						if (pozycjaRufy.x - i < 0)return false;//Sprawdzanie czy gracz próbuje ustawić statek poza planszą
						if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x - i] == 'z') return false;//Sprawdzanie bezpośrednio pól na których chcemy ustawić statek
						if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' - 1][pozycjaRufy.x + i] == 'z') return false;//Sprawdzanie czy na polach nad nie ma statku
						if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' + 1][pozycjaRufy.x + i] == 'z') return false;//Sprawdzanie czy na polach pod nie ma statku
					}
					if (pozycjaRufy.x - (dlugoscStatku - 1) - 1 >= 0) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x - (dlugoscStatku - 1) - 1] == 'z') return false;//Sprawdzanie czy pozycja po lewej nie jest zajęta przez inny statek
					if (pozycjaRufy.x + 1 <= 9) if (TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x + 1] == 'z') return false;//Sprawdzanie czy pozycja po prawej nie jest zajęta przez inny statek
				}
				//std::cout << "\nWolne\n";
				//wypiszPlansze();
				return true;
			}
			else {
				if (kierunek == polnoc) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if ((int)pozycjaRufy.y - 'A' - i < 0) return false;//Sprawdzanie czy gracz próbuje ustawić statek poza planszą
						if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' - i][pozycjaRufy.x] == 'z') return false;//Sprawdzanie bezpośrednio pól na których chcemy ustawić statek czy są puste
						if (pozycjaRufy.x - 1 >= 0) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' - i][pozycjaRufy.x - 1] == 'z') return false;//Sprawdzanie czy na polach po lewej nie ma statku
						if (pozycjaRufy.x + 1 <= 9) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' - i][pozycjaRufy.x + 1] == 'z') return false;//Sprawdzanie czy na polach po prawej nie ma statku
					}
					if ((int)pozycjaRufy.y - 'A' - (dlugoscStatku - 1) - 1 >= 0) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' - (dlugoscStatku - 1) - 1][pozycjaRufy.x] == 'z') return false;//Sprawdzanie pozycji nad statkiem czy nie jest zajęta przez inny statek
					if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' + 1][pozycjaRufy.x] == 'z') return false;//Sprawdzanie pozycji pod statkiem czy nie jest zajęta przez inny statek
				}
				else if (kierunek == poludnie) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if ((int)pozycjaRufy.y - 'A' + i > 10) return false;
						if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' + i][pozycjaRufy.x] == 'z') return false;
						if (pozycjaRufy.x - 1 >= 0) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' + i][pozycjaRufy.x - 1] == 'z') return false;//Sprawdzanie czy na polach po lewej nie ma statku
						if (pozycjaRufy.x + 1 <= 9) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' + i][pozycjaRufy.x + 1] == 'z') return false;//Sprawdzanie czy na polach po prawej nie ma statku
					}
					if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' - 1][pozycjaRufy.x] == 'z') return false;//Sprawdzanie pozycji nad statkiem czy nie jest zajęta przez inny statek
					if ((int)pozycjaRufy.y - 'A' + (dlugoscStatku - 1) + 1 <= 9) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' + (dlugoscStatku - 1) + 1][pozycjaRufy.x] == 'z') return false;//Sprawdzanie pozycji pod statkiem czy nie jest zajęta przez inny statek
				}
				else if (kierunek == wschod) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if (pozycjaRufy.x + i > 10) return false;
						if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x + i] == 'z') return false;
						if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' - 1][pozycjaRufy.x + i] == 'z') return false;//Sprawdzanie czy na polach nad nie ma statku
						if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' + 1][pozycjaRufy.x + i] == 'z') return false;//Sprawdzanie czy na polach pod nie ma statku
					}
					if (pozycjaRufy.x - 1 >= 0) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x - 1] == 'z') return false;//Sprawdzanie czy pozycja po lewej nie jest zajęta przez inny statek
					if (pozycjaRufy.x + (dlugoscStatku - 1) + 1 <= 9) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x + (dlugoscStatku - 1) + 1] == 'z') return false;//Sprawdzanie czy pozycja po prawej nie jest zajęta przez inny statek
				}
				else {//zachod
					for (i = 0; i < dlugoscStatku; ++i) {
						if (pozycjaRufy.x - i < 0)return false;//Sprawdzanie czy gracz próbuje ustawić statek poza planszą
						if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x - i] == 'z') return false;//Sprawdzanie bezpośrednio pól na których chcemy ustawić statek
						if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' - 1][pozycjaRufy.x + i] == 'z') return false;//Sprawdzanie czy na polach nad nie ma statku
						if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' + 1][pozycjaRufy.x + i] == 'z') return false;//Sprawdzanie czy na polach pod nie ma statku
					}
					if (pozycjaRufy.x - (dlugoscStatku - 1) - 1 >= 0) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x - (dlugoscStatku - 1) - 1] == 'z') return false;//Sprawdzanie czy pozycja po lewej nie jest zajęta przez inny statek
					if (pozycjaRufy.x + 1 <= 9) if (TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x + 1] == 'z') return false;//Sprawdzanie czy pozycja po prawej nie jest zajęta przez inny statek
				}
				//std::cout << "\nWolne\n";
				//wypiszPlansze();
				return true;
			}
		}

		//Funkcja ustawiająca statek
		void ustawStatek(short dlugoscStatku, Punkt pozycjaRufy, Kierunek kierunek, bool gracz) {
			short i;
			if (gracz == 0) {
				if (kierunek == polnoc) {
					for (i = 0; i < dlugoscStatku; ++i) {
						TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' - i][pozycjaRufy.x] = 'z';
					}
				}
				else if (kierunek == wschod) {//wschod
					for (i = 0; i < dlugoscStatku; ++i) {
						TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x + i] = 'z';
					}
				}
				else if (kierunek == poludnie) {//poludnie
					for (i = 0; i < dlugoscStatku; ++i) {
						TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A' + i][pozycjaRufy.x] = 'z';
					}
				}
				else {//zachod
					for (i = 0; i < dlugoscStatku; ++i) {
						TabPlanszaGraczaLudzkiego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x - i] = 'z';//zmiana statusu pola na zajete
					}
				}
				wypiszPlansze();
			}
			else {
				if (kierunek == polnoc) {
					for (i = 0; i < dlugoscStatku; ++i) {
						TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' - i][pozycjaRufy.x] = 'z';
					}
				}
				else if (kierunek == wschod) {//wschod
					for (i = 0; i < dlugoscStatku; ++i) {
						TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x + i] = 'z';
					}
				}
				else if (kierunek == poludnie) {//poludnie
					for (i = 0; i < dlugoscStatku; ++i) {
						TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A' + i][pozycjaRufy.x] = 'z';
					}
				}
				else {//zachod
					for (i = 0; i < dlugoscStatku; ++i) {
						TabPlanszaGraczaKomputerowego[(int)pozycjaRufy.y - 'A'][pozycjaRufy.x - i] = 'z';//zmiana statusu pola na zajete
					}
				}
				wypiszPlansze();
			}
		}

};