#pragma once

#include <list>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Bullet.h"

using namespace std;
using namespace sf;

class Wall
{
private:
	RectangleShape rect;
	bool destructible{ false };

public:
	Wall(Vector2f p, float sz, bool destr);
	bool isDestructible() const;
	const IntRect& getTextureRect();
	void draw_with(RenderWindow& win);
};

