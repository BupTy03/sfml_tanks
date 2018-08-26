#pragma once

#include <iostream>
#include <array>
#include <list>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Bullet.h"

using namespace std;
using namespace sf;

class Tank
{
protected:
	Vector2f currPos{ 0.f,0.f };
	float sizeRect{ 0.f };
	Direction currDir{ Direction::FRONT };
	array <RectangleShape, 6> rects;
	Color color;
	list<Bullet> bullets;
	Clock step_timer;
	Clock shot_timer;
	IntRect textureRect;

	// перестраивает танк в заданном направлении
	void rebuild();
	void make_step();
	void drawBullets(RenderWindow& win);
	void setTextureRect();

public:
	explicit Tank();
	explicit Tank(Vector2f pos, float sizeR, Direction dir, Color col);
	virtual void draw_with(RenderWindow& win);
	void make_shot();
	void setDirection(Direction d);
	IntRect& getTextureRect();
	list<Bullet>& getBullets();
};

