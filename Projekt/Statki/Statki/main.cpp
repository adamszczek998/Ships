#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");//stworzenie okna 200x200
	sf::CircleShape shape(100.f);//stworzenie obiektu kolo
	shape.setFillColor(sf::Color::Green);//ustawienie koloru

	while (window.isOpen())//glowna petla 
	{
		sf::Event event;
		while (window.pollEvent(event))//³apie wszystkie eventy
		{
			if (event.type == sf::Event::Closed)//wy³apuje czy event to klikniêcie krzy¿yka
				window.close();//zamyka okno
		}

		window.clear();//nie rozmazuje siê jak na XP
		window.draw(shape);//render kola (kszta³tu)
		window.display();//wyœwietla okno
	}

	return 0;
}