#include "EnemyTank.h"

void EnemyTank::draw_with(RenderWindow& win)
{
	this->setTextureRect();

	if ((enemy_timer.getElapsedTime()).asSeconds() >= 3.f)
	{
		if (rand_bool())
		{
			this->make_shot();
		}
	}

	if ((enemy_timer.getElapsedTime()).asSeconds() >= 5.f)
	{
		this->setDirection(static_cast<Direction>(rand_int(0, 3)));
		enemy_timer.restart();
	}

	this->rebuild();
	Tank::draw_with(win);
}
