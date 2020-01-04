#pragma once
#include "Gracz.h"


class GraczKomputerowy : public Gracz {
	friend class GraczLudzki;
	const sf::Event* _event;
	const sf::Window* _window;
	sf::RectangleShape kwadratKursora;
	FazaGry fazaGry;
	bool finishedTurn = false;
	int liczbaStatkowDoRozstawienia;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		
		target.draw(*planszaGraczaLudzkiego);
		target.draw(*planszaGraczaKomputerowego);
		//for (int i = 0; i < rozstawioneStatki.size(); i++) {
		//	target.draw(rozstawioneStatki[i]);
		//}
		//target.draw(kwadratKursora);
		//target.draw(statki[indeksAktualnegoStatku]);
	
	}
public:

	GraczKomputerowy(const sf::Event* event, const sf::Window* window, int* indexAktualnegoGracza) {
		_indexAktualnegoGracza = indexAktualnegoGracza;
		_event = event;//
		_window = window;//

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
		
		
	}

	~GraczKomputerowy() {
		
	}

	virtual  void DoTurn() override {
		FazaRozstawienia();
		*_indexAktualnegoGracza = 0;
		//std::cout <<"#"<< _indexAktualnegoGracza<<"#";
		return;
	}

	void FazaRozstawienia() {
		statkiKomputera[0].setKierunek(polnoc, 1);
		statkiKomputera[0].setPozycjaRufy({ 0, 'B' }, 1);
		statkiKomputera[1].setKierunek(poludnie, 1);
		statkiKomputera[1].setPozycjaRufy({ 7, 'B' }, 1);
		statkiKomputera[2].setKierunek(wschod, 1);
		statkiKomputera[2].setPozycjaRufy({ 1, 'E' }, 1);
		statkiKomputera[3].setKierunek(zachod, 1);
		statkiKomputera[3].setPozycjaRufy({ 7, 'H' }, 1);
		//std::cout << "2";
		indeksAktualnegoStatku = 0;
		while (indeksAktualnegoStatku < statkiKomputera.size()-1) {
			std::cout << indeksAktualnegoStatku << std::endl;
			if (planszaGraczaLudzkiego->sprawdzCzyWolne(statkiKomputera[indeksAktualnegoStatku].getDlugoscStatku(), statkiKomputera[indeksAktualnegoStatku].getPozycja(), statkiKomputera[indeksAktualnegoStatku].getKierunek(), 1)) {
				//przeniesienie aktualnego statku do rozstawionych statków
				rozstawioneStatkiKomputera.push_back(statkiKomputera[indeksAktualnegoStatku]);
				planszaGraczaLudzkiego->ustawStatek(statkiKomputera[indeksAktualnegoStatku].getDlugoscStatku(), statkiKomputera[indeksAktualnegoStatku].getPozycja(), statkiKomputera[indeksAktualnegoStatku].getKierunek(), 1);

				liczbaStatkowDoRozstawienia--;
				if (liczbaStatkowDoRozstawienia > 0) {
					++indeksAktualnegoStatku;
				}
			}
			//std::cout << ;
		}
		std::cout << "3";
		
		
	}

};