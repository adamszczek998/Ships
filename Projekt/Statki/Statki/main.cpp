#include <SFML/Graphics.hpp>
//#include "Plansza.h"
//#include "GraczLudzki.h"
//#include "GraczKomputerowy.h"
#include "Game.h"

int main(){
	
	Game Gra;
	Gra.PlayGame();


	//const int windowSizeX = 1620;
	//const int windowSizeY = 900;
	//sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Statki");
	//
	//sf::Event event;
	//int indexAktualnegoGracza = 1;
	//int staryIndex = 1;

	//Plansza* planszaGraczaLudzkiego = nullptr;
	//Plansza* planszaGraczaKomputerowego = nullptr;
	//planszaGraczaLudzkiego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 0.f), sf::Color(15, 101, 176));
	//planszaGraczaKomputerowego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(820.f, 0.f), sf::Color(13, 73, 127));

	//Gracz* gracze[2];
	//gracze[0] = new GraczLudzki(&event, &window, &indexAktualnegoGracza, planszaGraczaLudzkiego, planszaGraczaKomputerowego);
	//gracze[1] = new GraczKomputerowy(&event, &window, &indexAktualnegoGracza, planszaGraczaLudzkiego, planszaGraczaKomputerowego);
	//Gracz* aktualnyGracz = gracze[indexAktualnegoGracza];
	//

	//while (window.isOpen()) {//glowna petla 
	//	while (window.pollEvent(event)) {//lapie wszystkie eventy

	//		aktualnyGracz->DoTurn();
	//		//std::cout << "Stary: " << staryIndex << "\n";
	//		//std::cout << "Aktualny: " << indexAktualnegoGracza << "\n";
	//		if (staryIndex != indexAktualnegoGracza) {
	//			staryIndex = indexAktualnegoGracza;
	//			aktualnyGracz = gracze[indexAktualnegoGracza];
	//			//std::cout << "q";
	//		}
	//		if (event.type == sf::Event::Closed)//wylapuje czy event to klikniecie krzyzyka
	//			window.close();//zamyka okno
	//	}
	//	window.clear();//nie rozmazuje sie jak na XP
	//	window.draw(*aktualnyGracz);//render planszy
	//	
	//	window.display();//wyswietla okno
	//}

	//delete planszaGraczaKomputerowego;
	//delete planszaGraczaLudzkiego;
	//delete gracze[0];
	//delete gracze[1];




	return 0;
}