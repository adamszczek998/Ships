#include <SFML/Graphics.hpp>
#include "plansza.h"
#include "GraczLudzki.h"

int main(){

	const int windowSizeX = 1620;
	const int windowSizeY = 900;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Statki");

	//Testowe wypisywanie planszy i ustawianie okrętu
	/*
	planszaRozstawienia.wypiszPlansze();
	Punkt punkt;
	punkt.x = 5;
	punkt.y = 'E';
	planszaRozstawienia.ustawStatek(3, punkt, polnoc);
	std::cout << "\n\n";
	planszaRozstawienia.wypiszPlansze();*/
	//===============================================

	sf::Event event;
	Gracz* gracz1 = new GraczLudzki(&event, &window);

	while (window.isOpen()) {//glowna petla 
		while (window.pollEvent(event)) {//lapie wszystkie eventy
			gracz1->DoTurn();
			if (event.type == sf::Event::Closed)//wylapuje czy event to klikniecie krzyzyka
				window.close();//zamyka okno
		}
		window.clear();//nie rozmazuje sie jak na XP
		window.draw(*gracz1);//render planszy
		
		window.display();//wyswietla okno
	}

	return 0;
}