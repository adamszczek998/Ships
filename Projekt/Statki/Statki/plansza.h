#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
struct Punkt {
	short x;
	char y;

};

enum Kierunek { polnoc = 0, wschod = 1, poludnie = 2, zachod = 3 };

class Plansza : public sf::Drawable { //dziedziczenie
	private:
		sf::RectangleShape plansza;

		sf::Color kolorPlansza;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(plansza);
		}
		char planszaTab[10][10];//p-pusty, z-zajety, s-strzelany
	public:
		Plansza(sf::Vector2f size, sf::Vector2f position, sf::Color kolorPlansza) : kolorPlansza(kolorPlansza) {
			plansza.setSize(size);
			plansza.setPosition(position);
			plansza.setFillColor(kolorPlansza);
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) planszaTab[i][j] = 'p';
			}
		}
		
		//testowa funkcja wypisująca planszę w konsoli
		void wypiszPlansze() {
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j) std::cout<<planszaTab[i][j]<<" ";
				std::cout << "\n";
			}
		}
		//============================================
		
		bool sprawdzCzyWolne(short dlugoscStatku, Punkt pozycjaRufy, Kierunek kierunek) {
		//	short w=0;
			//while(w<2){
				short i;
				if (kierunek == polnoc) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if (pozycjaRufy.x - i < 0)return false;
						if (planszaTab[pozycjaRufy.x - i][(int)pozycjaRufy.y - 'A'] == 'z') return false;
						//if (w == 1) planszaTab[pozycjaRufy.x - i][(int)pozycjaRufy.y - 'A'] = 'z';
					}
				}
				else if (kierunek == wschod) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if ((int)pozycjaRufy.y - 'A' + i > 10) return false;
						if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' + i] == 'z') return false;
						//if (w == 1) planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' + i] = 'z';
					}
				}
				else if (kierunek == poludnie) {
					for (i = 0; i < dlugoscStatku; ++i) {
						if (pozycjaRufy.x + i > 10) return false;
						if (planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 'A'] == 'z') return false;
						//if (w == 1) planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 'A'] = 'z';
					}
				}
				else{
					for (i = 0; i < dlugoscStatku; ++i) {
						if ((int)pozycjaRufy.y - 'A' - i < 0) return false;//czy poza plansza
						if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' - i] == 'z') return false;//czy puste pole
						//if (w == 1) planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 'A' - i] = 'z';//zmiana statusu pola na zajete
					}
				}
				//++w;
			//}
				std::cout << "\nWolne\n";
				return true;
		}
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