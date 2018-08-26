#include <SFML/Window.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Tank.h"
#include "GameMap.h"

using namespace std;
using namespace sf;

void update_my_window(RenderWindow& win, GameMap& g_map, Direction dir, bool shot)
{
	g_map.updateMainTank(dir, shot);
	g_map.drawAllWith(win);
}

int main()
{
	constexpr int win_size = 600;
	constexpr int size_in_items = 30;
	RenderWindow window(VideoMode(win_size, win_size), "WoT 3.0", sf::Style::Default);

	constexpr float size_of_item = win_size / static_cast<float>(size_in_items);

	GameMap game_map(size_of_item, size_in_items);

	game_map.emplaceMainTank(Vector2f(size_of_item * (size_in_items / 2), size_of_item * (size_in_items - 5)), size_of_item, Direction::FRONT, Color::Green);
	game_map.emplaceEnemy(Vector2f(size_of_item * (size_in_items / 2), size_of_item * 3), size_of_item, Direction::BACK, Color::Red);
	game_map.emplaceEnemy(Vector2f(size_of_item * (size_in_items / 4), size_of_item * 3), size_of_item, Direction::FRONT, Color::Red);
	game_map.emplaceEnemy(Vector2f(size_of_item * (size_in_items / 10), size_of_item * 3), size_of_item, Direction::LEFT, Color::Red);

	if (!game_map.ParseFromFile("map.txt"))
	{
		cerr << "Error: file named \"map.txt\" unable to open" << endl;
	}

	Direction current_direction = Direction::FRONT;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) 
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::A)) 
		{
			current_direction = Direction::LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			current_direction = Direction::RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			current_direction = Direction::BACK;
		}
		else if(Keyboard::isKeyPressed(Keyboard::W))
		{
			current_direction = Direction::FRONT;
		}
		bool shot{ false };
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			shot = true;
		}

		window.clear();

		if (!game_map.computeLogic()) 
		{
			window.close();
		}

		update_my_window(window, game_map, current_direction, shot);

		window.display();
	}

	return 0;
}