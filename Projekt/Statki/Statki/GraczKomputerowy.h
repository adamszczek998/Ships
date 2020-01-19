#pragma once
#include "Gracz.h"
#include "GraczLudzki.h"

class GraczKomputerowy : public Gracz {
	friend class GraczLudzki;//
	const sf::Event* _event;
	const sf::Window* _window;
	Plansza* _planszaGraczaLudzkiego;
	Plansza* _planszaGraczaKomputerowego;
	sf::RectangleShape kwadratKursora;
	FazaGry fazaGry;
	int liczbaStatkowDoRozstawienia;
	int HPGraczaLudzkiego;
	Punkt pozycja;
	int stanAI;
	int kierunekCase;
	bool polnocB;
	bool wschodB;
	bool poludnieB;
	bool zachodB;
	std::vector<sf::CircleShape>* _trafionePola;
	std::vector<Statek>* _rozstawioneStatki;
	sf::Text* _GameInfo;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		
		target.draw(*_planszaGraczaLudzkiego);//
		target.draw(*_planszaGraczaKomputerowego);//
		for (int i = 0; i < _rozstawioneStatki->size(); i++) {
			target.draw((*_rozstawioneStatki)[i]);
		}
		for (int i = 0; i < _trafionePola->size(); ++i) {
			target.draw((*_trafionePola)[i]);
		}

		
	}
public:
//KONSTRUKTORY=============================================================================================

	GraczKomputerowy(const sf::Event* event, const sf::Window* window, int* indexAktualnegoGracza, Plansza* planszaGraczaLudzkiego, Plansza* planszaGraczaKomputerowego, std::vector<sf::CircleShape>* trafionePola, std::vector<Statek>* rozstawioneStatki, sf::Text* GameInfo) : stanAI(1), polnocB(0), wschodB(0), poludnieB(0), zachodB(0) {
		_indexAktualnegoGracza = indexAktualnegoGracza;
		_event = event;//
		_window = window;//
		_planszaGraczaLudzkiego = planszaGraczaLudzkiego;
		_planszaGraczaKomputerowego = planszaGraczaKomputerowego;
		_trafionePola = trafionePola;
		_rozstawioneStatki = rozstawioneStatki;
		_GameInfo = GameInfo;
		//planszaGraczaLudzkiego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 0.f), sf::Color(15, 101, 176));
		//planszaGraczaKomputerowego = new Plansza(sf::Vector2f(800.f, 800.f), sf::Vector2f(820.f, 0.f), sf::Color(13, 73, 127));

		Statek statek2(2, planszaGraczaLudzkiego);
		Statek statek3(3, planszaGraczaLudzkiego);
		Statek statek4(4, planszaGraczaLudzkiego);
		Statek statek5(5, planszaGraczaLudzkiego);
		statkiKomputera.push_back(statek2);
		statkiKomputera.push_back(statek3);
		statkiKomputera.push_back(statek4);
		statkiKomputera.push_back(statek5);
		liczbaStatkowDoRozstawienia = statkiKomputera.size();
		indeksAktualnegoStatku = 0;

		for (int i = 0; i < liczbaStatkowDoRozstawienia; ++i) {
			HPGraczaLudzkiego += statkiKomputera[i].getDlugoscStatku();
		}
		
	}

	
//DESTRUKTORY=============================================================================================

	~GraczKomputerowy() {
		
	}


//METODY=============================================================================================
	virtual  void DoTurn() override {
		if (fazaGry == STRZELANIE) FazaStrzelania();
		else if (fazaGry == ROZSTAWIENIE) FazaRozstawienia();
		else Koniec();
		//FazaRozstawienia();
		*_indexAktualnegoGracza = 0;
		//std::cout <<"#"<< _indexAktualnegoGracza<<"#";
		return;
	}

	void FazaRozstawienia() {
		/*statkiKomputera[0].setKierunek(polnoc, 1);
		statkiKomputera[0].setPozycjaRufy({ 0, 'B' }, 1);
		statkiKomputera[1].setKierunek(poludnie, 1);
		statkiKomputera[1].setPozycjaRufy({ 7, 'B' }, 1);
		statkiKomputera[2].setKierunek(wschod, 1);
		statkiKomputera[2].setPozycjaRufy({ 1, 'E' }, 1);
		statkiKomputera[3].setKierunek(zachod, 1);
		statkiKomputera[3].setPozycjaRufy({ 7, 'H' }, 1);*/


		//std::cout << "2";
		indeksAktualnegoStatku = 0;
		while (indeksAktualnegoStatku < statkiKomputera.size()) {
			//std::cout << indeksAktualnegoStatku << std::endl;

			srand(time(NULL));
			kierunekCase = std::rand() % 4;
			pozycja.x = std::rand() % 10;
			pozycja.y = char(std::rand() % 10 + 'A');
			statkiKomputera[indeksAktualnegoStatku].setKierunek(Kierunek(kierunekCase), 1);
			statkiKomputera[indeksAktualnegoStatku].setPozycjaRufy(pozycja, 1);

			if (_planszaGraczaLudzkiego->sprawdzCzyWolne(statkiKomputera[indeksAktualnegoStatku].getDlugoscStatku(), statkiKomputera[indeksAktualnegoStatku].getPozycja(), statkiKomputera[indeksAktualnegoStatku].getKierunek(), 1)) {
				//przeniesienie aktualnego statku do rozstawionych statkow
				rozstawioneStatkiKomputera.push_back(statkiKomputera[indeksAktualnegoStatku]);
				_planszaGraczaLudzkiego->ustawStatek(statkiKomputera[indeksAktualnegoStatku].getDlugoscStatku(), statkiKomputera[indeksAktualnegoStatku].getPozycja(), statkiKomputera[indeksAktualnegoStatku].getKierunek(), 1);

				liczbaStatkowDoRozstawienia--;
				if (liczbaStatkowDoRozstawienia >= 0) {
					++indeksAktualnegoStatku;
				}
			}
			//std::cout << ;
		}
		//std::cout << "3";
		fazaGry = STRZELANIE;
		
	}

	void FazaStrzelania() {
		srand(time(NULL));
		
		try{
			switch (stanAI) {
			case 1://losowy ostrzal
				
				polnocB = 0;
				wschodB = 0;
				poludnieB = 0;
				zachodB = 0;

				do {//szukanie losowych niestrzelanych punktow
					
					pozycja.x = std::rand() % 10;
					pozycja.y = char(std::rand() % 10 + 'A');
				} while (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 's');

				if (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 'z') {
					stanAI = 2;
					Trafienie();
				}
				else Pudlo();

				//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
				break;

			case 2://trafiono i szuka wektor
				do {
					
					if (polnocB == 1 && poludnieB == 1 && wschodB == 1 && zachodB == 1) {
						std::string safeBreakMessage = "Nie udalo sie znalezc kierunku w AIswitch: case2, error_code #0001";
						throw safeBreakMessage;
					}
					
					kierunekCase = std::rand() % 4;
					std::cout << kierunekCase << "\t";
					if (kierunekCase == 0 && polnocB == 0) {//sprawdza czy kierunek spalony
						if ((int(pozycja.y) - 'A' - 1) >= 0) {//sprawdza czy poza plansza
							//pozycja.y--;//potencjalny error
							if (_planszaGraczaLudzkiego->sprawdzStatus({ pozycja.x,pozycja.y - 1 }, 0) == 'z') {//sprawdza czy na danym polu jest statek
								--pozycja.y;
								stanAI = 3;//znaleziony wektor
								std::cout <<"stanAI: "<< stanAI << "\t";
								//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
								Trafienie();
							}
							else {
								polnocB = 1;//spalony kierunek
								--pozycja.y;
								Pudlo();
								++pozycja.y;
							}
							break;
						}
						else polnocB = 1;
					}
					if (kierunekCase == 1 && wschodB == 0) {
						if((pozycja.x + 1) <= 9){
							//pozycja.x++;//potencjalny error
							if (_planszaGraczaLudzkiego->sprawdzStatus({ pozycja.x + 1, pozycja.y }, 0) == 'z') {
								++pozycja.x;
								stanAI = 4;
								//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
								Trafienie();
							}
							else {
								wschodB = 1;
								++pozycja.x;
								Pudlo();
								--pozycja.x;
							}
							break;
						}
						else wschodB = 1;
					}
					if (kierunekCase == 2 && poludnieB == 0) {
						if ((int(pozycja.y) - 'A' + 1) <= 9) {
							//pozycja.y++;//potencjalny error
							if (_planszaGraczaLudzkiego->sprawdzStatus({ pozycja.x, pozycja.y + 1 }, 0) == 'z') {
								++pozycja.y;
								stanAI = 5;
								//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
								Trafienie();
							}
							else {
								poludnieB = 1;
								++pozycja.y;
								Pudlo();
								--pozycja.y;
							}
							break;
						}
						else poludnieB = 1;
					}
					if (kierunekCase == 3 && zachodB==0) {
						if ((pozycja.x - 1) >= 0) {
							//pozycja.x--;//potencjalny error
							if (_planszaGraczaLudzkiego->sprawdzStatus({ pozycja.x - 1, pozycja.y }, 0) == 'z') {
								--pozycja.x;
								stanAI = 6;
								//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
								Trafienie();
							}
							else {
								zachodB = 1;
								--pozycja.x;
								Pudlo();
								++pozycja.x;
							}
							break;
						}
						else zachodB = 1;
					}
				} while (true);
				break;

			case 3://polnoc
				while (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 's') {//przechodzi przez wszystkie strzelane pola
					if ((int)pozycja.y - 'A' - 1 >= 0) --pozycja.y;//sprawdza czy poza plansza
					else {
						if (poludnieB == 0)stanAI = 5;//poludnie
						else {
							/*polnocB = 0;
							wschodB = 0;
							poludnieB = 0;
							zachodB = 0;*/
							stanAI = 1;
							break;
						}
						polnocB = 1;
						break;//koniec planszy
					}
				}
				if (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 'z') {
					Trafienie();
					//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
				}
				else if (poludnieB == 0) {
					stanAI = 5;//poludnie
					Pudlo();
					//++pozycja.y;
				}
				else {
					/*polnocB = 0;
					wschodB = 0;
					poludnieB = 0;
					zachodB = 0;*/
					Pudlo();
					stanAI = 1;
					break;
				}
				polnocB = 1;
				break;

			case 4://wschod
				while (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 's') {//przechodzi przez wszystkie strzelane pola
					if (pozycja.x + 1 <= 9) ++pozycja.x;//sprawdza czy poza plansza
					else {
						if (zachodB == 0)stanAI = 6;//poludnie
						else {
							/*polnocB = 0;
							wschodB = 0;
							poludnieB = 0;
							zachodB = 0;*/
							stanAI = 1;
							break;
						}
						wschodB = 1;
						break;//koniec planszy
					}
				}
				if (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 'z') {
					Trafienie();
					//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
				}
				else if (zachodB == 0) {
					stanAI = 6;//zachod
					Pudlo();
					//--pozycja.x;
				}
				else {
					/*polnocB = 0;
					wschodB = 0;
					poludnieB = 0;
					zachodB = 0;*/
					Pudlo();
					stanAI = 1;
					break;
				}
				zachodB = 1;
				break;

			case 5://poludnie
				while (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 's') {//przechodzi przez wszystkie strzelane pola
					if ((int)pozycja.y - 'A' + 1 <= 9) ++pozycja.y;//sprawdza czy poza plansza
					else {
						if (polnocB == 0)stanAI = 3;//poludnie
						else {
							/*polnocB = 0;
							wschodB = 0;
							poludnieB = 0;
							zachodB = 0;*/
							stanAI = 1;
							break;
						}
						poludnieB = 1;
						break;//koniec planszy
					}
				}
				if (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 'z') {
					Trafienie();
					//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
				}
				else if (polnocB == 0) {
					stanAI = 3;//polnoc
					Pudlo();
					//--pozycja.y;
				}
				else {
					/*polnocB = 0;
					wschodB = 0;
					poludnieB = 0;
					zachodB = 0;*/
					Pudlo();
					stanAI = 1;
					break;
				}
				poludnieB = 1;
				break;

			case 6://zachod
				while (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 's') {//przechodzi przez wszystkie strzelane pola
					if (pozycja.x - 1 >= 0) --pozycja.x;//sprawdza czy poza plansza
					else {
						if (wschodB == 0)stanAI = 4;//poludnie
						else {
							/*polnocB = 0;
							wschodB = 0;
							poludnieB = 0;
							zachodB = 0;*/
							stanAI = 1;
							break;
						}
						zachodB = 1;
						break;//koniec planszy
					}
				}
				if (_planszaGraczaLudzkiego->sprawdzStatus(pozycja, 0) == 'z') {
					Trafienie();
					//_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
				}
				else if (wschodB == 0) {
					stanAI = 4;//wschod
					Pudlo();
					//++pozycja.x;
				}
				else {
					/*polnocB = 0;
					wschodB = 0;
					poludnieB = 0;
					zachodB = 0;*/
					Pudlo();
					stanAI = 1;
					break;
				}
				zachodB = 1;
				break;

			default:
				std::string safeBreakMessage = "Nie udalo sie wybrać stanu AI w AIswitch: default, error_code #0003";
				throw safeBreakMessage;
				 
			}
		}
		catch (std::string Message) {
			//system("cls");
			std::cout << Message<<"\t"<<pozycja.x<<pozycja.y;
			std::cin.get();
		}

		//std::cout << "Komputer\n";

		if (HPGraczaLudzkiego > 0) *_indexAktualnegoGracza = 0;
		else fazaGry=KONIEC;
	}

	void Koniec() {
		std::cout << "Wygral komputer";
		_GameInfo->setString(L"Zmierzasz na spotkanie z Posejdonem. Przegrywasz.");
		//std::cin.get();
	}

	void Trafienie() {
		_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
		sf::CircleShape trafienie(20);
		trafienie.setPosition({ float(pozycja.x * 80 + 20), float((int(pozycja.y) - 'A') * 80 + 20) });
		trafienie.setFillColor(sf::Color(171, 52, 39));
		_trafionePola->push_back(trafienie);
		std::cout << "\n" << pozycja.x << pozycja.y << "\n";
		--HPGraczaLudzkiego;
	}

	void Pudlo() {
		_planszaGraczaLudzkiego->zmienStatus(pozycja, 0);
		sf::CircleShape trafienie(20);
		trafienie.setPosition({ float(pozycja.x * 80 + 20), float((int(pozycja.y) - 'A') * 80 + 20) });
		trafienie.setFillColor(sf::Color(157, 159, 163));
		_trafionePola->push_back(trafienie);
	}
};