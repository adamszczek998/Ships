#pragma once
#include "Gracz.h"

enum FazaGry { ROZSTAWIENIE, STRZELANIE };

class GraczLudzki : public Gracz {
	friend class GraczKomputerowy;
	const sf::Event* _event;
	const sf::Window* _window;
	
	sf::RectangleShape kwadratKursora;
	FazaGry fazaGry;
	bool finishedTurn = false;
	int liczbaStatkowDoRozstawienia;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		
		//target.draw(*planszaGraczaLudzkiego);
		//target.draw(*planszaGraczaKomputerowego);
		for (int i = 0; i < rozstawioneStatki.size(); i++){
			target.draw(rozstawioneStatki[i]);
		}
		target.draw(kwadratKursora);
		target.draw(statki[indeksAktualnegoStatku]);
	}
public:
//KONSTRUKTORY=============================================================================================
	GraczLudzki(const sf::Event* event, const sf::Window* window, int* indexAktualnegoGracza) {
		_indexAktualnegoGracza = indexAktualnegoGracza;
		_event = event;		
		_window = window;
		planszaGraczaLudzkiego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 0.f), sf::Color(15, 101, 176));
		planszaGraczaKomputerowego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(820.f, 0.f), sf::Color(13, 73, 127));

		Statek statek2(2, planszaGraczaLudzkiego);
		Statek statek3(3, planszaGraczaLudzkiego);
		Statek statek4(4, planszaGraczaLudzkiego);
		Statek statek5(5, planszaGraczaLudzkiego);
		statki.push_back(statek2);
		statki.push_back(statek3);
		statki.push_back(statek4);
		statki.push_back(statek5);

		indeksAktualnegoStatku = 0;
		//tu sie bedzie dzialo cale dodawanie statkow??
		liczbaStatkowDoRozstawienia = statki.size();
		kwadratKursora.setSize({ 80, 80 });
		kwadratKursora.setPosition({ 0, 0 });
		kwadratKursora.setFillColor(sf::Color::White);
		fazaGry = ROZSTAWIENIE;
	}

//DESTRUKTORY==============================================================================================
	~GraczLudzki(){
		delete planszaGraczaLudzkiego;
		delete planszaGraczaKomputerowego;
	}
	
	//Obs³uga faz gry
	virtual  void DoTurn() override { 
		if (fazaGry == STRZELANIE) FazaStrzelania(); 
		else if (fazaGry == ROZSTAWIENIE) FazaRozstawienia();
	}

	void FazaRozstawienia(){
		if (liczbaStatkowDoRozstawienia==0) { fazaGry = STRZELANIE; return; } 
		if (_event->type == sf::Event::MouseMoved) {//ruch myszy==========================================================================================================
			if (sf::Mouse::getPosition(*_window).y < 800) {
				if (sf::Mouse::getPosition(*_window).x < 800) {
					Punkt pozycjaMyszy = { (sf::Mouse::getPosition(*_window).x / 80), char((sf::Mouse::getPosition(*_window).y / 80)) };
					kwadratKursora.setPosition({ (float)pozycjaMyszy.x * 80,(float)pozycjaMyszy.y * 80 });
					statki[indeksAktualnegoStatku].setPozycjaRufy({ (int)pozycjaMyszy.x, pozycjaMyszy.y + 'A' }, 0);
				}
				else if (sf::Mouse::getPosition(*_window).x > 820) {
					kwadratKursora.setPosition({ float((sf::Mouse::getPosition(*_window).x / 80) * 80 + 20), float((sf::Mouse::getPosition(*_window).y / 80) * 80) });
				}
			}//==========================================================================================================================================================
		}
		else if (_event->type == sf::Event::KeyPressed) {//klikniecie klawisza=========================================================================================
			if (_event->key.code == sf::Keyboard::Q) {
				if (statki[indeksAktualnegoStatku].getKierunek() == 0) statki[indeksAktualnegoStatku].setKierunek((Kierunek)3, 0);
				else statki[indeksAktualnegoStatku].setKierunek(Kierunek(statki[indeksAktualnegoStatku].getKierunek() - 1), 0);
				//std::cout << "Kierunek: " << aktualnyStatek.getKierunek() << std::endl;
			}
			else if (_event->key.code == sf::Keyboard::E) {
				if (statki[indeksAktualnegoStatku].getKierunek() == 3) statki[indeksAktualnegoStatku].setKierunek((Kierunek)0, 0);
				else statki[indeksAktualnegoStatku].setKierunek(Kierunek(statki[indeksAktualnegoStatku].getKierunek() + 1), 0);
				//std::cout << "Kierunek: " << aktualnyStatek.getKierunek() << std::endl;
			}//==========================================================================================================================================================
		}
		else if (_event->type == sf::Event::MouseButtonPressed) {//klikniecie klawisza myszy============================================================================
			if (_event->key.code == sf::Mouse::Left) {
				if (sf::Mouse::getPosition(*_window).y <= 800) {
					if (sf::Mouse::getPosition(*_window).x <= 800) {
						Punkt pozycjaRufyRozstawienie = { sf::Mouse::getPosition(*_window).x / 80, char(sf::Mouse::getPosition(*_window).y / 80 + 'A') };
						std::cout << pozycjaRufyRozstawienie.x << " " << pozycjaRufyRozstawienie.y << std::endl;
						std::cout << sf::Mouse::getPosition(*_window).x << "\t" << sf::Mouse::getPosition(*_window).y << std::endl;
						if (planszaGraczaLudzkiego->sprawdzCzyWolne(statki[indeksAktualnegoStatku].getDlugoscStatku(), pozycjaRufyRozstawienie, statki[indeksAktualnegoStatku].getKierunek(), 0)){
							//przeniesienie aktualnego statku do rozstawionych statków
							rozstawioneStatki.push_back(statki[indeksAktualnegoStatku]);
							planszaGraczaLudzkiego->ustawStatek(statki[indeksAktualnegoStatku].getDlugoscStatku(), pozycjaRufyRozstawienie, statki[indeksAktualnegoStatku].getKierunek(), 0);
							//TODO zmiana koloru rozstawionego statku
							liczbaStatkowDoRozstawienia--;
							if (liczbaStatkowDoRozstawienia > 0) {
								++indeksAktualnegoStatku;
							}
						}
					}
					else if (sf::Mouse::getPosition(*_window).x >= 820) {
						Punkt pozycjaStrzal = { (sf::Mouse::getPosition(*_window).x - 820) / 80, char(sf::Mouse::getPosition(*_window).y / 80 + 'A') };
						std::cout << pozycjaStrzal.x << " " << pozycjaStrzal.y << std::endl;
					}
				}
			}
		}//==============================================================================================================================================================
	}

	void FazaStrzelania(){

		_indexAktualnegoGracza = 0;
	}

	bool FinishedTurn(){

	}
};
