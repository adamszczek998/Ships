#pragma once
#include <SFML/Graphics.hpp>
#include "Plansza.h"
#include "GraczLudzki.h"
#include "GraczKomputerowy.h"

class Game {
public:
	const int windowSizeX = 1620;
	const int windowSizeY = 900;
	sf::Event event;
	sf::RenderWindow* window;
	
	int indexAktualnegoGracza/* = 1*/;
	int staryIndex/* = 1*/;

	Plansza* planszaGraczaLudzkiego/* = nullptr*/;
	Plansza* planszaGraczaKomputerowego/* = nullptr*/;

	//std::unique_ptr<Plansza> planszaGraczaLudzkiego

	std::vector<sf::CircleShape> trafionePola;

	Gracz* gracze[2];
	Gracz* aktualnyGracz = gracze[indexAktualnegoGracza];

public:
	Game() : indexAktualnegoGracza(1), staryIndex(1) {

		//std::unique_ptr<Plansza> planszaGraczaLudzkiego(new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 0.f), sf::Color(15, 101, 176)));
		//std::unique_ptr<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(windowSizeX, windowSizeY), "Statki"));
		//std::unique_ptr<GraczLudzki> gracze[1](new GraczLudzki(&event, window, &indexAktualnegoGracza, /*&**/planszaGraczaLudzkiego, planszaGraczaKomputerowego));
		
		planszaGraczaLudzkiego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 0.f), sf::Color(15, 101, 176));
		planszaGraczaKomputerowego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(820.f, 0.f), sf::Color(13, 73, 127));

		window = new sf::RenderWindow(sf::VideoMode(windowSizeX, windowSizeY), "Statki");
		gracze[0] = new GraczLudzki(&event, window, &indexAktualnegoGracza, /*&**/planszaGraczaLudzkiego, planszaGraczaKomputerowego, &trafionePola);
		gracze[1] = new GraczKomputerowy(&event, window, &indexAktualnegoGracza, /*&**/planszaGraczaLudzkiego, planszaGraczaKomputerowego, &trafionePola);
		
		aktualnyGracz = gracze[indexAktualnegoGracza];
	}
	~Game() {
		delete planszaGraczaKomputerowego;
		//delete planszaGraczaLudzkiego;
		delete gracze[0];
		delete gracze[1];
	}

	void PlayGame(){
		//sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Statki");
		//gracze[0] = new GraczLudzki(&event, &window, &indexAktualnegoGracza, planszaGraczaLudzkiego, planszaGraczaKomputerowego);
		//gracze[1] = new GraczKomputerowy(&event, &window, &indexAktualnegoGracza, planszaGraczaLudzkiego, planszaGraczaKomputerowego);

		while (window->isOpen()) {//glowna petla 
			while (window->pollEvent(event)) {//lapie wszystkie eventy
				/*window->pollEvent(event);*/
				aktualnyGracz->DoTurn();
				
				if (staryIndex != indexAktualnegoGracza) {
					staryIndex = indexAktualnegoGracza;
					aktualnyGracz = gracze[indexAktualnegoGracza];
				}
				if (event.type == sf::Event::Closed) window->close();//zamyka okno
			}
			window->clear();//nie rozmazuje sie jak na XP
			window->draw(*aktualnyGracz);//render planszy
			
			window->display();//wyswietla okno
		}
	}
};