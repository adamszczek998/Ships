#include <SFML/Graphics.hpp>
#include "plansza.h"
int main()
{
	const int windowSizeX = 1620;
	const int windowSizeY = 900;
	sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "SFML works!");//stworzenie okna 200x200
/*
	sf::RectangleShape planszaRozstawienia(sf::Vector2f(800, 800));//stworzenie obiektu kszta�tu
	sf::RectangleShape planszaStrzalu(sf::Vector2f(800, 800));//stworzenie obiektu kszta�tu
	planszaRozstawienia.setPosition(0.f, 100.f);
	planszaStrzalu.setPosition(820.f, 100.f);
	sf::Color kolorPlanszaRozstawienia(15,101,176);
	sf::Color kolorPlanszaStrzalu(13, 73, 127);
	planszaRozstawienia.setFillColor(kolorPlanszaRozstawienia);//ustawienie koloru
	planszaStrzalu.setFillColor(sf::Color::Blue);//ustawienie koloru
	*/
	Plansza planszaRozstawienia(sf::Vector2f(800.f, 800.f), sf::Vector2f(0.f, 100.f), sf::Color(15, 101, 176));
	Plansza planszaStrzalu(sf::Vector2f(800.f, 800.f), sf::Vector2f(820.f, 100.f), sf::Color(13, 73, 127));

	//Testowe wypisywanie planszy i ustawianie okrętu
	planszaRozstawienia.wypiszPlansze();
	Punkt punkt;
	punkt.x = 1;
	punkt.y = 'E';
	planszaRozstawienia.ustawStatek(3, punkt, zachod);
	std::cout << "\n\n";
	planszaRozstawienia.wypiszPlansze();
	//===============================================

	while (window.isOpen())//glowna petla 
	{
		sf::Event event;
		while (window.pollEvent(event))//�apie wszystkie eventy
		{
			if (event.type == sf::Event::Closed)//wy�apuje czy event to klikni�cie krzy�yka
				window.close();//zamyka okno
		}

		window.clear();//nie rozmazuje si� jak na XP
		window.draw(planszaRozstawienia);//render kola (kszta�tu)
		window.draw(planszaStrzalu);
		window.display();//wy�wietla okno
	}

	return 0;
}