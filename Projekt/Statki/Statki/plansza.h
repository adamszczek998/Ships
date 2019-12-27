#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Punkt {
	int x;
	char y;
};

enum Kierunek { polnoc = 0, wschod = 1, poludnie = 2, zachod = 3 };//przenieść do klasy. Obecnie błędy

class Plansza : public sf::Drawable { //dziedziczenie po SFMLu
	private:
		sf::RectangleShape plansza;
		sf::Color kolorPlansza;
		char planszaTab[10][10] = {};//p-pusty, z-zajety, s-strzelany

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
				for (int j = 0; j < 10; ++j) planszaTab[i][j] = 'p';
			}
		}

//METODY==============================================================================================================================================================
		
		//Testowa funkcja wypisująca planszę w konsoli
		void wypiszPlansze() {
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) std::cout<<planszaTab[i][j]<<" ";
				std::cout << "\n";
			}
		}
		//============================================
		
		//Funkcja sprawdzająca czy podane pola są wolne
		bool sprawdzCzyWolne(short dlugoscStatku, Punkt pozycjaRufy, Kierunek kierunek) {
		
				short i;
				if (kierunek == polnoc) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if ((int)pozycjaRufy.y - 'A' - i < 0) return false;//Sprawdzanie czy gracz próbuje ustawić statek poza planszą
						if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' - i] == 'z') return false;//Sprawdzanie bezpośrednio pól na których chcemy ustawić statek czy są puste
						if (pozycjaRufy.x - 1 >= 0) if (planszaTab[pozycjaRufy.x - 1][(int)pozycjaRufy.y - 'A' - i] == 'z') return false;//Sprawdzanie czy na polach po lewej nie ma statku
						if (pozycjaRufy.x + 1 <= 9) if (planszaTab[pozycjaRufy.x + 1][(int)pozycjaRufy.y - 'A' - i] == 'z') return false;//Sprawdzanie czy na polach po prawej nie ma statku
					}
					if ((int)pozycjaRufy.y - 'A' - (dlugoscStatku - 1) - 1 >= 0) if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' - (dlugoscStatku - 1) - 1] == 'z') return false;//Sprawdzanie pozycji nad statkiem czy nie jest zajęta przez inny statek
					if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' + 1] == 'z') return false;//Sprawdzanie pozycji pod statkiem czy nie jest zajęta przez inny statek
				}
				else if (kierunek == poludnie) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if ((int)pozycjaRufy.y - 'A' + i > 10) return false;
						if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' + i] == 'z') return false;
						if (pozycjaRufy.x - 1 >= 0) if (planszaTab[pozycjaRufy.x - 1][(int)pozycjaRufy.y - 'A' - i] == 'z') return false;//Sprawdzanie czy na polach po lewej nie ma statku
						if (pozycjaRufy.x + 1 <= 9) if (planszaTab[pozycjaRufy.x + 1][(int)pozycjaRufy.y - 'A' - i] == 'z') return false;//Sprawdzanie czy na polach po prawej nie ma statku
					}
					if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' - 1] == 'z') return false;//Sprawdzanie pozycji nad statkiem czy nie jest zajęta przez inny statek
					if ((int)pozycjaRufy.y - 'A' + (dlugoscStatku - 1) + 1 <= 9) if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' + (dlugoscStatku - 1) + 1] == 'z') return false;//Sprawdzanie pozycji pod statkiem czy nie jest zajęta przez inny statek
				}
				else if (kierunek == wschod) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if (pozycjaRufy.x + i > 10) return false;
						if (planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 'A'] == 'z') return false;
						if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 'A' - 1] == 'z') return false;//Sprawdzanie czy na polach nad nie ma statku
						if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 'A' + 1] == 'z') return false;//Sprawdzanie czy na polach pod nie ma statku
					}
					if (pozycjaRufy.x - 1 >= 0) if (planszaTab[pozycjaRufy.x-1][(int)pozycjaRufy.y - 'A'] == 'z') return false;//Sprawdzanie czy pozycja po lewej nie jest zajęta przez inny statek
					if (pozycjaRufy.x + (dlugoscStatku - 1) + 1 <= 9) if (planszaTab[pozycjaRufy.x + (dlugoscStatku - 1) + 1][(int)pozycjaRufy.y - 'A'] == 'z') return false;//Sprawdzanie czy pozycja po prawej nie jest zajęta przez inny statek
				}
				else{//zachod
					for (i = 0; i < dlugoscStatku; ++i) {
						if (pozycjaRufy.x - i < 0)return false;//Sprawdzanie czy gracz próbuje ustawić statek poza planszą
						if (planszaTab[pozycjaRufy.x - i][(int)pozycjaRufy.y - 'A'] == 'z') return false;//Sprawdzanie bezpośrednio pól na których chcemy ustawić statek
						if ((int)pozycjaRufy.y - 'A' - 1 >= 0) if (planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 'A' - 1] == 'z') return false;//Sprawdzanie czy na polach nad nie ma statku
						if ((int)pozycjaRufy.y - 'A' + 1 <= 9) if (planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 'A' + 1] == 'z') return false;//Sprawdzanie czy na polach pod nie ma statku
					}
					if (pozycjaRufy.x - (dlugoscStatku - 1) - 1 >= 0) if (planszaTab[pozycjaRufy.x - (dlugoscStatku - 1) - 1][(int)pozycjaRufy.y - 'A'] == 'z') return false;//Sprawdzanie czy pozycja po lewej nie jest zajęta przez inny statek
					if (pozycjaRufy.x + 1 <= 9) if (planszaTab[pozycjaRufy.x + 1][(int)pozycjaRufy.y - 'A'] == 'z') return false;//Sprawdzanie czy pozycja po prawej nie jest zajęta przez inny statek
				}
				std::cout << "\nWolne\n";
				return true;
		}

		//Funkcja ustawiająca statek
		void ustawStatek(short dlugoscStatku, Punkt pozycjaRufy, Kierunek kierunek) {
			short i;
			if (kierunek == polnoc) {
				for (i = 0; i < dlugoscStatku; ++i) {
					planszaTab[pozycjaRufy.x - i][(int)pozycjaRufy.y - 'A'] = 'z';
				}
			}
			else if (kierunek == wschod) {
				for (i = 0; i < dlugoscStatku; ++i) {
					planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' + i] = 'z';
				}
			}
			else if (kierunek == poludnie) {
				for (i = 0; i < dlugoscStatku; ++i) {
					planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 'A'] = 'z';
				}
			}
			else {
				for (i = 0; i < dlugoscStatku; ++i) {
					planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' - i] = 'z';//zmiana statusu pola na zajete
				}
			}
		}

};