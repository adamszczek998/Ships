#pragma once
#include <vector>
#include "Statek.h"
#include <SFML/Graphics.hpp>

class Gracz : public sf::Drawable {
protected:
	std::vector<Statek> statki;
	int indeksAktualnegoStatku = 0;
	Plansza* planszaGraczaLudzkiego = nullptr;
	Plansza* planszaGraczaKomputerowego = nullptr;
	std::vector<Statek> rozstawioneStatki;
public:
	virtual void DoTurn() = 0;
};