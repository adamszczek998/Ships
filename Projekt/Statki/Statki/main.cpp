#include <SFML/Graphics.hpp>
#include "ksztalt.h"
int main()
{
	const int windowSizeX = 1620;
	const int windowSizeY = 900;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "SFML works!");//stworzenie okna 200x200
/*
	sf::RectangleShape planszaRozstawienia(sf::Vector2f(800, 800));//stworzenie obiektu kszta³tu
	sf::RectangleShape planszaStrzalu(sf::Vector2f(800, 800));//stworzenie obiektu kszta³tu
	planszaRozstawienia.setPosition(0.f, 100.f);
	planszaStrzalu.setPosition(820.f, 100.f);
	sf::Color kolorPlanszaRozstawienia(15,101,176);
	sf::Color kolorPlanszaStrzalu(13, 73, 127);
	planszaRozstawienia.setFillColor(kolorPlanszaRozstawienia);//ustawienie koloru
	planszaStrzalu.setFillColor(sf::Color::Blue);//ustawienie koloru
	*/
	Plansza planszaRozstawienia(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 100.f), sf::Color(15, 101, 176));
	Plansza planszaStrzalu(sf::Vector2f(800.f, 800.f), sf::Vector2f(820.f, 100.f), sf::Color(13, 73, 127));





	while (window.isOpen())//glowna petla 
	{
		sf::Event event;
		while (window.pollEvent(event))//³apie wszystkie eventy
		{
			if (event.type == sf::Event::Closed)//wy³apuje czy event to klikniêcie krzy¿yka
				window.close();//zamyka okno
		}

		window.clear();//nie rozmazuje siê jak na XP
		window.draw(planszaRozstawienia);//render kola (kszta³tu)
		window.draw(planszaStrzalu);
		window.display();//wyœwietla okno
	}

	return 0;
}