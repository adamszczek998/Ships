#pragma once
#include <vector>
#include "Statek.h"
#include <SFML/Graphics.hpp>

class Gracz : public sf::Drawable {
protected:
	std::vector<Statek> statki;
	std::vector<Statek> statkiKomputera;
	int indeksAktualnegoStatku = 0;
	int* _indexAktualnegoGracza = nullptr;
	//Plansza* planszaGraczaLudzkiego = nullptr;
	//Plansza* planszaGraczaKomputerowego = nullptr;
	std::vector<Statek> rozstawioneStatki;
	std::vector<Statek> rozstawioneStatkiKomputera;

public:
	virtual void DoTurn() = 0;

};