#pragma once
#include <SFML/Graphics.hpp>


class Plansza : public sf::Drawable { //dziedziczenie
	private:
		sf::RectangleShape plansza;
		sf::Color kolorPlansza;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(plansza);
		}
	public:
		Plansza(sf::Vector2f size, sf::Vector2f position, sf::Color kolorPlansza) : kolorPlansza(kolorPlansza) 
		{
			plansza.setSize(size);
			plansza.setPosition(position);
			plansza.setFillColor(kolorPlansza);
		}


};