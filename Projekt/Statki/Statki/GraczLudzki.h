#pragma once
#include "Gracz.h"

enum FazaGry { ROZSTAWIENIE, STRZELANIE, KONIEC };

class GraczLudzki : public Gracz {
	friend class GraczKomputerowy;

	Plansza* _planszaGraczaLudzkiego;
	Plansza* _planszaGraczaKomputerowego;
	std::vector<sf::CircleShape>* _trafionePola;
	std::vector<Statek>* _rozstawioneStatki;
	sf::Text* _GameInfo;
	const sf::Event* _event;
	const sf::Window* _window;
	sf::RectangleShape kwadratKursora;

	FazaGry fazaGry;
	int liczbaStatkowDoRozstawienia;
	int HPGraczaKomputerowego;

	Punkt pozycja;
	Punkt pozycjaStrzalu;

	//Metoda rysujaca plansze, statki, trafienia i pudla
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(*_planszaGraczaLudzkiego);
		target.draw(*_planszaGraczaKomputerowego);
		for (int i = 0; i < _rozstawioneStatki->size(); i++){
			target.draw((*_rozstawioneStatki)[i]);
		}
		target.draw(kwadratKursora);
		if(fazaGry == ROZSTAWIENIE)target.draw(statki[indeksAktualnegoStatku]);
		for (int i = 0; i < _trafionePola->size(); ++i) {
			target.draw((*_trafionePola)[i]);
		}
	}
public:
//KONSTRUKTORY============================================================================

	GraczLudzki(const sf::Event* event, const sf::Window* window, int* indexAktualnegoGracza, Plansza* planszaGraczaLudzkiego, Plansza* planszaGraczaKomputerowego, std::vector<sf::CircleShape>* trafionePola, std::vector<Statek>* rozstawioneStatki, sf::Text* GameInfo) {
		_indexAktualnegoGracza = indexAktualnegoGracza;
		_event = event;		
		_window = window;
		_planszaGraczaLudzkiego = planszaGraczaLudzkiego;
		_planszaGraczaKomputerowego = planszaGraczaKomputerowego;
		_trafionePola = trafionePola;
		_rozstawioneStatki = rozstawioneStatki;
		_GameInfo = GameInfo;

		Statek statek2(2, planszaGraczaLudzkiego);
		Statek statek3(3, planszaGraczaLudzkiego);
		Statek statek4(4, planszaGraczaLudzkiego);
		Statek statek5(5, planszaGraczaLudzkiego);
		statki.push_back(statek2);
		statki.push_back(statek3);
		statki.push_back(statek4);
		statki.push_back(statek5);
		liczbaStatkowDoRozstawienia = statki.size();
		indeksAktualnegoStatku = 0;

		for (int i = 0; i < liczbaStatkowDoRozstawienia; ++i) {//obliczenie liczby hp na podstawie dlugosci statkow
			HPGraczaKomputerowego += statki[i].getDlugoscStatku();
		}

		kwadratKursora.setSize({ 80, 80 });
		kwadratKursora.setPosition({ 0, 0 });
		kwadratKursora.setFillColor(sf::Color::White);

		fazaGry = ROZSTAWIENIE;
	}

//DESTRUKTORY=============================================================================
	~GraczLudzki(){

	}
	

//METODY==================================================================================

	//Metoda polimorficzna zarzadzajaca fazami gry
	virtual  void DoTurn() override { 
		if (fazaGry == STRZELANIE) FazaStrzelania();
		else if (fazaGry == ROZSTAWIENIE) FazaRozstawienia();
		else Koniec();
	}

	//Metoda pozwalajaca graczowi rozmiescic statki
	void FazaRozstawienia(){
		if (liczbaStatkowDoRozstawienia==0) { 
			fazaGry = STRZELANIE; 
			*_indexAktualnegoGracza = 1;
			return; 
		} 
		_GameInfo->setString("Ustaw swoje statki");
		if (_event->type == sf::Event::MouseMoved) {//ruch myszy
			if (sf::Mouse::getPosition(*_window).y < 800) {
				if (sf::Mouse::getPosition(*_window).x < 800) {
					Punkt pozycjaMyszy = { (sf::Mouse::getPosition(*_window).x / 80), char((sf::Mouse::getPosition(*_window).y / 80)) };
					kwadratKursora.setPosition({ (float)pozycjaMyszy.x * 80,(float)pozycjaMyszy.y * 80 });
					statki[indeksAktualnegoStatku].setPozycjaRufy({ (int)pozycjaMyszy.x, pozycjaMyszy.y + 'A' }, 0);
				}
				else if (sf::Mouse::getPosition(*_window).x > 820) {
					kwadratKursora.setPosition({ float((sf::Mouse::getPosition(*_window).x / 80) * 80 + 20), float((sf::Mouse::getPosition(*_window).y / 80) * 80) });
				}
			}
		}
		else if (_event->type == sf::Event::KeyPressed) {//klikniecie klawisza
			if (_event->key.code == sf::Keyboard::Q) {
				if (statki[indeksAktualnegoStatku].getKierunek() == 0) statki[indeksAktualnegoStatku].setKierunek((Kierunek)3, 0);
				else statki[indeksAktualnegoStatku].setKierunek(Kierunek(statki[indeksAktualnegoStatku].getKierunek() - 1), 0);
			}
			else if (_event->key.code == sf::Keyboard::E) {
				if (statki[indeksAktualnegoStatku].getKierunek() == 3) statki[indeksAktualnegoStatku].setKierunek((Kierunek)0, 0);
				else statki[indeksAktualnegoStatku].setKierunek(Kierunek(statki[indeksAktualnegoStatku].getKierunek() + 1), 0);
			}
		}
		else if (_event->type == sf::Event::MouseButtonPressed) {//klikniecie klawisza myszy
			if (_event->key.code == sf::Mouse::Left){
				if (sf::Mouse::getPosition(*_window).y <= 800) {
					if (sf::Mouse::getPosition(*_window).x <= 800) {
						_GameInfo->setString(L" ");
						Punkt pozycjaRufyRozstawienie = { sf::Mouse::getPosition(*_window).x / 80, char(sf::Mouse::getPosition(*_window).y / 80 + 'A') };
						if (_planszaGraczaLudzkiego->sprawdzCzyWolne(statki[indeksAktualnegoStatku].getDlugoscStatku(), pozycjaRufyRozstawienie, statki[indeksAktualnegoStatku].getKierunek(), 0)){
							//przeniesienie aktualnego statku do rozstawionych statk�w
							_rozstawioneStatki->push_back(statki[indeksAktualnegoStatku]);
							_planszaGraczaLudzkiego->ustawStatek(statki[indeksAktualnegoStatku].getDlugoscStatku(), pozycjaRufyRozstawienie, statki[indeksAktualnegoStatku].getKierunek(), 0);
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
		}
	}

	//Metoda obslugujaca strzelanie
	void FazaStrzelania(){
		if (_event->type == sf::Event::MouseMoved) {//ruch myszy
			if (sf::Mouse::getPosition(*_window).y < 800) {
				if (sf::Mouse::getPosition(*_window).x < 800) {
					Punkt pozycjaMyszy = { (sf::Mouse::getPosition(*_window).x / 80), char((sf::Mouse::getPosition(*_window).y / 80)) };
					kwadratKursora.setPosition({ (float)pozycjaMyszy.x * 80,(float)pozycjaMyszy.y * 80 });
				}
				else if (sf::Mouse::getPosition(*_window).x > 820) {
					kwadratKursora.setPosition({ float((sf::Mouse::getPosition(*_window).x / 80) * 80 + 20), float((sf::Mouse::getPosition(*_window).y / 80) * 80) });
				}
			}
		}
		else if (_event->type == sf::Event::MouseButtonPressed) {//klikniecie klawisza myszy
			if (_event->key.code == sf::Mouse::Left) {
				if (sf::Mouse::getPosition(*_window).y <= 800) {
					if (sf::Mouse::getPosition(*_window).x >= 820) {
						pozycjaStrzalu = { (sf::Mouse::getPosition(*_window).x - 820) / 80, char(sf::Mouse::getPosition(*_window).y / 80 + 'A') };
						char statusPola = _planszaGraczaLudzkiego->sprawdzStatus(pozycjaStrzalu, 1);
						if (statusPola == 'p') {
							Pudlo();
							if (HPGraczaKomputerowego > 0)	*_indexAktualnegoGracza = 1;
							else fazaGry = KONIEC;
							return;
						}
						else if (statusPola == 'z') {
							Trafienie();
							if (HPGraczaKomputerowego > 0)	*_indexAktualnegoGracza = 1;
							else fazaGry = KONIEC;
							return;
						}
					}
				}
			}
		}
		if (HPGraczaKomputerowego == 0) fazaGry = KONIEC;
	}

	//Metoda wyswietlajaca komunikat o koncu gry
	void Koniec() {
		std::cout << "Wygral gracz";
		_GameInfo->setString(L"Wrog tonie wraz ze swoimi okretami. Wygrywasz!");
	}

	//Metoda zarzadzajaca trafieniem
	void Trafienie() {
		_planszaGraczaLudzkiego->zmienStatus(pozycjaStrzalu, 1);
		_GameInfo->setString(L"Trafienie!");
		sf::CircleShape trafienie(20);
		trafienie.setPosition({ float(pozycjaStrzalu.x * 80 + 840), float((int(pozycjaStrzalu.y) - 'A') * 80 + 20) });
		trafienie.setFillColor(sf::Color(171, 52, 39));
		_trafionePola->push_back(trafienie);
		--HPGraczaKomputerowego;
	}

	//Metoda zarzadzajaca pudlem
	void Pudlo() {
		_planszaGraczaLudzkiego->zmienStatus(pozycjaStrzalu, 1);
		_GameInfo->setString(L"Pudlo!");
		sf::CircleShape trafienie(20);
		trafienie.setPosition({ float(pozycjaStrzalu.x * 80 + 840), float((int(pozycjaStrzalu.y) - 'A') * 80 + 20) });
		trafienie.setFillColor(sf::Color(157, 159, 163));
		_trafionePola->push_back(trafienie);
	}
};
