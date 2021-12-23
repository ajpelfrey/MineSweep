#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include "Board.h"
using namespace sf;

int main()
{
	RenderWindow* window = new RenderWindow(VideoMode(800, 600), "Minesweeper");
	Board board;
	while (window->isOpen())
	{
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
			if (event.type == Event::MouseButtonPressed)
			{
				bool leftClick = (event.mouseButton.button == Mouse::Left);
				board.click(event.mouseButton.x, event.mouseButton.y, leftClick);
			}
		}

		window->clear(Color(255, 255, 255, 255));
		board.draw(window);
		window->display();
	}
}