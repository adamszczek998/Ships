#pragma once
#include <vector>
#include "Statek.h"
#include <SFML/Graphics.hpp>

class Gracz : public sf::Drawable {
protected:
	std::vector<Statek> statki;
	Statek aktualnyStatek;
	Plansza* planszaRozstawienia;
	Plansza* planszaStrzalu;
public:
	virtual void DoTurn() = 0;
};