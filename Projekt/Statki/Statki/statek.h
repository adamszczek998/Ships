#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "plansza.h"

class Statek : public sf::Drawable {
	private:
		short punktyZycia=3;
		short liczbaDostepnychStatkowDoRozstawienia = 1;
		short dlugoscStatku = 3;
		Kierunek kierunek = polnoc;
		Punkt pozycjaRufy = {4, 'E'};
		Plansza* _planszaGraczaLudzkiego = nullptr;

		sf::RectangleShape rufa;
		//std::vector<sf::RectangleShape> kadlub; //@
		sf::RectangleShape kadlub[3];
		sf::RectangleShape dziob;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(rufa);
//			for (int i = 0; i < kadlub.size(); ++i) {//@
//				target.draw(kadlub[i]);
//			}

			for (int i = 0; i < dlugoscStatku-2; ++i) {//@
				target.draw(kadlub[i]);
			}

			target.draw(dziob);
		}

	public:
//KONSTRUKTORY==============================================================================================================================================================
		Statek() : dlugoscStatku(3) {}
		//ustawia dlugosc statku
		Statek(short dlugosc, Plansza* planszaGraczaLudzkiego) : dlugoscStatku(dlugosc), punktyZycia(dlugosc), kierunek(Kierunek::polnoc), _planszaGraczaLudzkiego(planszaGraczaLudzkiego) {
			rufa.setSize({ 80, 80 });
			rufa.setPosition({ 320, 160 });
			rufa.setFillColor(sf::Color::Red);

			for (int i = 2; i < dlugoscStatku; ++i) {
				sf::RectangleShape nowyKadlub;
				nowyKadlub.setSize({ 80, 80 });
				nowyKadlub.setPosition({ 320, 80 });
				nowyKadlub.setFillColor(sf::Color::Yellow);
				//kadlub.push_back(nowyKadlub);@
				kadlub[i - 2] = nowyKadlub;
			}

			dziob.setSize({ 80, 80 });
			dziob.setPosition({ 320, 0 });
			dziob.setFillColor(sf::Color::Green);
		}
	
		//ustawia pozycje rufy na planszy
		void setPozycjaRufy(Punkt pozycja) {
			pozycjaRufy = pozycja;
		}

//METODY==============================================================================================================================================================
		void renderStatku(short dlugoscStatku, Punkt pozycjaRufy, Kierunek kierunek) {
			short i;
			//std::cout << "start";
			if (kierunek == polnoc) {
				rufa.setPosition({ (float)pozycjaRufy.x*80, (float)(((int)pozycjaRufy.y-'A') * 80) });
				for (i = 0; i < dlugoscStatku; ++i) {
					if (i < dlugoscStatku - 1) kadlub[i].setPosition({ (float)((pozycjaRufy.x) * 80),(float)(((int)pozycjaRufy.y - 'A' - i) * 80) });
					else dziob.setPosition({ (float)((pozycjaRufy.x) * 80),(float)(((int)pozycjaRufy.y - 'A' - i) * 80) });
				}
			}
			else if (kierunek == wschod) {
				rufa.setPosition({ (float)(pozycjaRufy.x * 80),(float)(((int)pozycjaRufy.y - 'A') * 80 )});
				for (i = 0; i < dlugoscStatku; ++i) {
					if (i < dlugoscStatku - 1)kadlub[i].setPosition({ (float)((pozycjaRufy.x + i) * 80),(float)(((int)pozycjaRufy.y - 'A') * 80) });
					else dziob.setPosition({ (float)((pozycjaRufy.x + i) * 80),(float)(((int)pozycjaRufy.y - 'A') * 80) });
				}
			}
			else if (kierunek == poludnie) {
				rufa.setPosition({ (float)(pozycjaRufy.x * 80),(float)(((int)pozycjaRufy.y - 'A') * 80 )});
				for (i = 0; i < dlugoscStatku; ++i) {
					if (i < dlugoscStatku - 1)kadlub[i].setPosition({ (float)((pozycjaRufy.x) * 80),(float)(((int)pozycjaRufy.y - 'A' + i) * 80) });
					else dziob.setPosition({ (float)((pozycjaRufy.x) * 80),(float)(((int)pozycjaRufy.y - 'A' + i) * 80) });
				}
			}
			else {//zachod
				rufa.setPosition({ (float)(pozycjaRufy.x * 80),(float)(((int)pozycjaRufy.y - 'A') * 80) });
				for (i = 0; i < dlugoscStatku; ++i) {
					if (i < dlugoscStatku - 1)kadlub[i].setPosition({ (float)((pozycjaRufy.x - i) * 80),(float)(((int)pozycjaRufy.y - 'A') * 80 )});
					else dziob.setPosition({ (float)((pozycjaRufy.x - i) * 80),(float)(((int)pozycjaRufy.y - 'A') * 80 )});
				}
			}
		}

		//ustawia kierunek statku
		void setKierunek(Kierunek podanyKierunek) {
			kierunek = podanyKierunek;
			
			if (_planszaGraczaLudzkiego->sprawdzCzyWolne(dlugoscStatku, pozycjaRufy, kierunek)) renderStatku(dlugoscStatku, pozycjaRufy, kierunek);
		}

		Kierunek getKierunek() const {
			return kierunek;
		}
		
		//dekrementuje HP
		void trafienie() {
			punktyZycia--;
		}
		//dekrementuje pozostala liczbe statkow do rozstawienia
		void rozstawiony() {
			liczbaDostepnychStatkowDoRozstawienia--;
		}
};