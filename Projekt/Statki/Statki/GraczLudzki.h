#pragma once
#include "Gracz.h"

class GraczLudzki : public Gracz {
	const sf::Event* _event;
	const sf::Window* _window;
	sf::RectangleShape kwadratKursora;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*planszaGraczaLudzkiego);
		target.draw(*planszaGraczaKomputerowego);
		target.draw(kwadratKursora);
		target.draw(aktualnyStatek);
	}
public:
	GraczLudzki(const sf::Event* event, const sf::Window* window) {
		_event = event;		
		_window = window;
		planszaGraczaLudzkiego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 0.f), sf::Color(15, 101, 176));
		planszaGraczaKomputerowego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(820.f, 0.f), sf::Color(13, 73, 127));
		Statek statek(3,planszaGraczaLudzkiego);
		statki.push_back(statek);
		aktualnyStatek = statki[0];

		kwadratKursora.setSize({ 80, 80 });
		kwadratKursora.setPosition({ 0, 0 });
		kwadratKursora.setFillColor(sf::Color::White);
	}
	~GraczLudzki(){
		delete planszaGraczaLudzkiego;
		delete planszaGraczaKomputerowego;
	}
	
	//Obs³uga ruchu myszy, zmiany kierunku, wybrania pola
	virtual  void DoTurn() override {
		if (_event->type == sf::Event::MouseMoved){//ruch myszy==========================================================================================================
			if (sf::Mouse::getPosition(*_window).y < 800) {
				if (sf::Mouse::getPosition(*_window).x < 800) {
					kwadratKursora.setPosition({ float((sf::Mouse::getPosition(*_window).x / 80) * 80), float((sf::Mouse::getPosition(*_window).y / 80) * 80) });
				}
				else if (sf::Mouse::getPosition(*_window).x > 820) {
					kwadratKursora.setPosition({ float((sf::Mouse::getPosition(*_window).x / 80) * 80 + 20), float((sf::Mouse::getPosition(*_window).y / 80) * 80) });
				}
			}//==========================================================================================================================================================
		} else if (_event->type == sf::Event::KeyPressed) {//klikniecie klawisza=========================================================================================
			if (_event->key.code == sf::Keyboard::Q){
				if (aktualnyStatek.getKierunek() == 0) aktualnyStatek.setKierunek((Kierunek)3);
				else aktualnyStatek.setKierunek(Kierunek(aktualnyStatek.getKierunek() - 1));
				std::cout << "Kierunek: " << aktualnyStatek.getKierunek() << std::endl;
			}
			else if (_event->key.code == sf::Keyboard::E){
				if (aktualnyStatek.getKierunek() == 3) aktualnyStatek.setKierunek((Kierunek)0);
				else aktualnyStatek.setKierunek(Kierunek(aktualnyStatek.getKierunek() + 1));
				std::cout << "Kierunek: " << aktualnyStatek.getKierunek() << std::endl;
			}//==========================================================================================================================================================
		}else if (_event->type == sf::Event::MouseButtonPressed) {//klikniecie klawisza myszy============================================================================
			if (_event->key.code == sf::Mouse::Left){
				if (sf::Mouse::getPosition(*_window).y <= 800) {
					if (sf::Mouse::getPosition(*_window).x <= 800) {
						Punkt pozycjaRufyRozstawienie = { sf::Mouse::getPosition(*_window).x / 80, char(sf::Mouse::getPosition(*_window).y / 80 + 'A') };
						std::cout << pozycjaRufyRozstawienie.x << " " << pozycjaRufyRozstawienie.y << std::endl;
						std::cout << sf::Mouse::getPosition(*_window).x << "\t" << sf::Mouse::getPosition(*_window).y << std::endl;
					}
					else if (sf::Mouse::getPosition(*_window).x >= 820) {
						Punkt pozycjaStrzal = { (sf::Mouse::getPosition(*_window).x - 820) / 80, char(sf::Mouse::getPosition(*_window).y / 80 + 'A') };
						std::cout << pozycjaStrzal.x << " " << pozycjaStrzal.y << std::endl;
					}
				}
			}
		}//==============================================================================================================================================================
		
	};

};
