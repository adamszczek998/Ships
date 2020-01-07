#pragma once

#include <SFML/Graphics.hpp>
//#include "GraczKomputerowy.h"
#include "Gracz.h"

class Render : public Gracz {
	const sf::Event* _event;
	const sf::Window* _window;
	sf::RectangleShape kwadratKursora;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		target.draw(*planszaGraczaLudzkiego);
		target.draw(*planszaGraczaKomputerowego);

		for (int i = 0; i < rozstawioneStatki.size(); ++i) {
			target.draw(rozstawioneStatki[i]);
		}
		for (int i = 0; i < rozstawioneStatkiKomputera.size(); ++i) {
			target.draw(rozstawioneStatkiKomputera[i]);
		}

		target.draw(kwadratKursora);
		target.draw(statki[indeksAktualnegoStatku]);

	}

	Render(const sf::Window* window) {
		_window = window;//
	
	}



};
