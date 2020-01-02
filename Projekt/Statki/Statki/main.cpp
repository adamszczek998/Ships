#include <SFML/Graphics.hpp>
#include "plansza.h"
#include "GraczLudzki.h"

int main(){

	const int windowSizeX = 1620;
	const int windowSizeY = 900;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Statki");

	sf::Event event;
//	Gracz* gracz1 = new GraczLudzki(&event, &window);
	Gracz* gracze[2];
	gracze[0] = new GraczLudzki(&event, &window);
	Gracz* aktualnyGracz = gracze[0];
	//gracze[1] =
	
	while (window.isOpen()) {//glowna petla 
		while (window.pollEvent(event)) {//lapie wszystkie eventy
			aktualnyGracz->DoTurn();		
			if (event.type == sf::Event::Closed)//wylapuje czy event to klikniecie krzyzyka
				window.close();//zamyka okno
		}
		window.clear();//nie rozmazuje sie jak na XP
		window.draw(*aktualnyGracz);//render planszy
		
		window.display();//wyswietla okno
	}

	return 0;
}