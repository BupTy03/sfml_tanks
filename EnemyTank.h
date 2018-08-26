#pragma once

#include <random>
#include <time.h>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Tank.h"

inline int rand_int(int _min, int _max)
{
	return _min + rand() % (_max - _min + 1);
}

inline bool rand_bool()
{
	return static_cast<bool>(rand_int(0, 1));
}

class EnemyTank : public Tank
{
private:
	Clock enemy_timer;

public:
	explicit EnemyTank() : Tank()
	{
		srand(time(nullptr));
	}
	explicit EnemyTank(Vector2f pos, float sizeR, Direction dir, Color col = Color::Red) : Tank(pos, sizeR, dir, col) { srand(time(nullptr)); }

	void draw_with(RenderWindow& win) override final;
};

