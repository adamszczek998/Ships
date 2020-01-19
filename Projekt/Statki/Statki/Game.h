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
	sf::Font Font1942;
	sf::Text GameInfo;
	int indexAktualnegoGracza/* = 1*/;
	int staryIndex/* = 1*/;

	Plansza* planszaGraczaLudzkiego/* = nullptr*/;
	Plansza* planszaGraczaKomputerowego/* = nullptr*/;

	//std::unique_ptr<Plansza> planszaGraczaLudzkiego

	std::vector<sf::CircleShape> trafionePola;
	std::vector<Statek> rozstawioneStatki;

	Gracz* gracze[2];
	Gracz* aktualnyGracz = gracze[indexAktualnegoGracza];

public:
	Game() : indexAktualnegoGracza(1), staryIndex(1) {

		try{
			if (!Font1942.loadFromFile("1942.ttf")){
				std::string Error = "Blad krytyczny, nie udalo sie wczytac czcionki 1942.tff error_code #0004";
				throw Error;
			}
		}
		catch (std::string Error) {
			std::cout << Error;
			getchar();
			exit(1);
		}
		GameInfo.setFont(Font1942);
		GameInfo.setCharacterSize(24);
		GameInfo.setFillColor(sf::Color::White);
		GameInfo.setPosition({ 10.f, 820.f});
		
		
		planszaGraczaLudzkiego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 0.f), sf::Color(15, 101, 176));
		planszaGraczaKomputerowego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(820.f, 0.f), sf::Color(13, 73, 127));

		window = new sf::RenderWindow(sf::VideoMode(windowSizeX, windowSizeY), "Statki", /*sf::Style::Titlebar,*/ sf::Style::Close);
		gracze[0] = new GraczLudzki(&event, window, &indexAktualnegoGracza, /*&**/planszaGraczaLudzkiego, planszaGraczaKomputerowego, &trafionePola, &rozstawioneStatki, &GameInfo);
		gracze[1] = new GraczKomputerowy(&event, window, &indexAktualnegoGracza, /*&**/planszaGraczaLudzkiego, planszaGraczaKomputerowego, &trafionePola, &rozstawioneStatki, &GameInfo);
		
		aktualnyGracz = gracze[indexAktualnegoGracza];
	}
	~Game() {
		delete planszaGraczaKomputerowego;
		delete planszaGraczaLudzkiego;
		delete gracze[0];
		delete gracze[1];
	}

	void PlayGame(){

		while (window->isOpen()) {//glowna petla 
			while (window->pollEvent(event)) {//lapie wszystkie eventy
				/*window->pollEvent(event);*/
				aktualnyGracz->DoTurn();
				
				if (staryIndex != indexAktualnegoGracza) {
					staryIndex = indexAktualnegoGracza;
					aktualnyGracz = gracze[indexAktualnegoGracza];
				}
				if (event.type == sf::Event::Closed) {
					window->close();//zamyka okno
					exit(0);
				}
				if (event.type == sf::Event::KeyPressed) {//klikniecie klawisza=========================================================================================
					if (event.key.code == sf::Keyboard::Escape) {
						exit(0);
					}
				}
			}
			window->clear();//nie rozmazuje sie jak na XP
			window->draw(*aktualnyGracz);//render planszy
			window->draw(GameInfo);
			window->display();//wyswietla okno
		}
	}
};