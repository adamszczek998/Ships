#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");//stworzenie okna 200x200
	sf::CircleShape shape(100.f);//stworzenie obiektu kolo
	shape.setFillColor(sf::Color::Green);//ustawienie koloru

	while (window.isOpen())//glowna petla 
	{
		sf::Event event;
		while (window.pollEvent(event))//�apie wszystkie eventy
		{
			if (event.type == sf::Event::Closed)//wy�apuje czy event to klikni�cie krzy�yka
				window.close();//zamyka okno
		}

		window.clear();//nie rozmazuje si� jak na XP
		window.draw(shape);//render kola (kszta�tu)
		window.display();//wy�wietla okno
	}

	return 0;
}