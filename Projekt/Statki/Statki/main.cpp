#include <SFML/Graphics.hpp>
#include "plansza.h"
#include "GraczLudzki.h"
#include "GraczKomputerowy.h"

int main(){

	const int windowSizeX = 1620;
	const int windowSizeY = 900;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Statki");

	sf::Event event;
	int indexAktualnegoGracza = 1;
	int staryIndex = 1;
	Gracz* gracze[2];
	gracze[0] = new GraczLudzki(&event, &window, &indexAktualnegoGracza);
	gracze[1] = new GraczKomputerowy(&event, &window, &indexAktualnegoGracza);
	Gracz* aktualnyGracz = gracze[indexAktualnegoGracza];
	
	
	while (window.isOpen()) {//glowna petla 
		while (window.pollEvent(event)) {//lapie wszystkie eventy
			aktualnyGracz->DoTurn();
			//std::cout << "Stary: " << staryIndex << "\n";
			//std::cout << "Aktualny: " << indexAktualnegoGracza << "\n";
			if (staryIndex != indexAktualnegoGracza) {
				staryIndex = indexAktualnegoGracza;
				aktualnyGracz = gracze[indexAktualnegoGracza];
				std::cout << "q";
			}
			if (event.type == sf::Event::Closed)//wylapuje czy event to klikniecie krzyzyka
				window.close();//zamyka okno
		}
		window.clear();//nie rozmazuje sie jak na XP
		window.draw(*aktualnyGracz);//render planszy
		
		window.display();//wyswietla okno
	}

	return 0;
}