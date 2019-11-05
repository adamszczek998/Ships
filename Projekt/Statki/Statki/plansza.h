#pragma once
#include <SFML/Graphics.hpp>
#include "statek.h"
#include <iostream>


class Plansza : public sf::Drawable { //dziedziczenie
	private:
		sf::RectangleShape plansza;
		sf::Color kolorPlansza;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(plansza);
		}
		char planszaTab[10][10];//p-pusty, z-zajety, s-strzelany
	public:
		Plansza(sf::Vector2f size, sf::Vector2f position, sf::Color kolorPlansza) : kolorPlansza(kolorPlansza) 
		{
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

		bool ustawStatek(short dlugoscStatku, Punkt pozycjaRufy, Kierunek kierunek) {
			bool w=0;
			while(w<2){
				short i;
				if (kierunek == polnoc) {
					for (i = 0; i < dlugoscStatku; ++i){
						if ((int)pozycjaRufy.y - 65 - i < 0) return false;//czy poza plansza
						if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 65 - i] == 'z') return false;//czy puste pole
						if (w == 1) planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 65 - i] = 'z';//zmiana statusu pola na zajete
					}
				}
				else if (kierunek == poludnie) {
					for (i = 0; i < dlugoscStatku; ++i){
						if ((int)pozycjaRufy.y - 65 + i > 10) return false;
						if (planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 65 + i] == 'z') return false;
						if (w == 1) planszaTab[pozycjaRufy.x][(int)pozycjaRufy.y - 65 + i] = 'z';
					}
				}
				else if (kierunek == wschod) {
					for (i = 0; i < dlugoscStatku; ++i){
						if (pozycjaRufy.x + i > 10) return false;
						if (planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 65] == 'z') return false;
						if (w == 1) planszaTab[pozycjaRufy.x + i][(int)pozycjaRufy.y - 65] = 'z';
					}
				}
				else{
					for (i = 0; i < dlugoscStatku; ++i){
						if (pozycjaRufy.x - i < 0)return false;
						if (planszaTab[pozycjaRufy.x - i][(int)pozycjaRufy.y - 65] == 'z') return false;
						if (w == 1) planszaTab[pozycjaRufy.x - i][(int)pozycjaRufy.y - 65] = 'z';
					}
				}
				++w;
			}
		}
};