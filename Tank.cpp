#include "Tank.h"

Tank::Tank(){}

Tank::Tank(Vector2f pos, float sizeR, Direction dir, Color col = Color::Green) : currPos(pos), sizeRect(sizeR), currDir(dir), color(col)
{
	for (RectangleShape& r : rects)
	{
		r.setSize(Vector2f(sizeRect, sizeRect));
		r.setFillColor(color);
		r.setOutlineThickness(-sizeRect / 6.f);
		r.setOutlineColor(Color::Blue);
	}

	this->setTextureRect();
	rebuild();
}

void Tank::draw_with(RenderWindow& win)
{
	if ((step_timer.getElapsedTime()).asSeconds() >= 1.f)
	{
		this->make_step();
		step_timer.restart();
	}

	if (currPos.x < -sizeRect)
	{
		currPos.x = win.getSize().x;
	}
	else if (currPos.x > win.getSize().x + sizeRect)
	{
		currPos.x = 0;
	}
	if (currPos.y < -sizeRect)
	{
		currPos.y = win.getSize().y;
	}
	else if (currPos.y > win.getSize().y + sizeRect)
	{
		currPos.y = 0;
	}

	for (RectangleShape& rsh : rects){
		win.draw(rsh);
	}

	this->drawBullets(win);
}

void Tank::rebuild()
{
	switch (currDir)
	{
	case Direction::FRONT:
		rects.at(0).setPosition(Vector2f(currPos.x + sizeRect, currPos.y));
		rects.at(1).setPosition(Vector2f(currPos.x, currPos.y + sizeRect));
		rects.at(2).setPosition(Vector2f(currPos.x + sizeRect, currPos.y + sizeRect));
		rects.at(3).setPosition(Vector2f(currPos.x + sizeRect * 2.f, currPos.y + sizeRect));
		rects.at(4).setPosition(Vector2f(currPos.x, currPos.y + sizeRect * 2.f));
		rects.at(5).setPosition(Vector2f(currPos.x + sizeRect * 2.f, currPos.y + sizeRect * 2.f));
		return;
	case Direction::BACK:
		rects.at(0).setPosition(Vector2f(currPos.x + sizeRect, currPos.y + sizeRect * 2.f));
		rects.at(1).setPosition(Vector2f(currPos.x + sizeRect * 2.f, currPos.y + sizeRect));
		rects.at(2).setPosition(Vector2f(currPos.x + sizeRect, currPos.y + sizeRect));
		rects.at(3).setPosition(Vector2f(currPos.x, currPos.y + sizeRect));
		rects.at(4).setPosition(Vector2f(currPos.x, currPos.y));
		rects.at(5).setPosition(Vector2f(currPos.x + sizeRect * 2.f, currPos.y));
		return;
	case Direction::LEFT:
		rects.at(0).setPosition(Vector2f(currPos.x, currPos.y + sizeRect));
		rects.at(1).setPosition(Vector2f(currPos.x + sizeRect, currPos.y + sizeRect * 2.f));
		rects.at(2).setPosition(Vector2f(currPos.x + sizeRect, currPos.y + sizeRect));
		rects.at(3).setPosition(Vector2f(currPos.x + sizeRect, currPos.y));
		rects.at(4).setPosition(Vector2f(currPos.x + sizeRect * 2.f, currPos.y + sizeRect * 2.f));
		rects.at(5).setPosition(Vector2f(currPos.x + sizeRect * 2.f, currPos.y));
		return;
	case Direction::RIGHT:
		rects.at(0).setPosition(Vector2f(currPos.x + sizeRect * 2.f, currPos.y + sizeRect));
		rects.at(1).setPosition(Vector2f(currPos.x + sizeRect, currPos.y));
		rects.at(2).setPosition(Vector2f(currPos.x + sizeRect, currPos.y + sizeRect));
		rects.at(3).setPosition(Vector2f(currPos.x + sizeRect, currPos.y + sizeRect * 2.f));
		rects.at(4).setPosition(Vector2f(currPos.x, currPos.y));
		rects.at(5).setPosition(Vector2f(currPos.x, currPos.y + sizeRect * 2.f));
		return;
	}
}

void Tank::make_step()
{
	switch (currDir)
	{
	case Direction::FRONT:
		currPos.y -= sizeRect;
		break;
	case Direction::BACK:
		currPos.y += sizeRect;
		break;
	case Direction::LEFT:
		currPos.x -= sizeRect;
		break;
	case Direction::RIGHT:
		currPos.x += sizeRect;
		break;
	}
	this->setTextureRect();
}

void Tank::make_shot()
{
	if (shot_timer.getElapsedTime().asSeconds() >= 0.5f)
	{
		float size_bullet = sizeRect * 0.75f;
		Vector2f pos_bullet = (rects.at(0)).getPosition();

		switch (currDir)
		{
		case Direction::BACK:
			pos_bullet.x += sizeRect / 2.f - size_bullet / 2.f;
			pos_bullet.y = pos_bullet.y + sizeRect - size_bullet;
			break;
		case Direction::FRONT:
			pos_bullet.x += sizeRect / 2.f - size_bullet / 2.f;
			break;
		case Direction::LEFT:
			pos_bullet.y += sizeRect / 2.f - size_bullet / 2.f;
			break;
		case Direction::RIGHT:
			pos_bullet.x = pos_bullet.x + sizeRect - size_bullet;
			pos_bullet.y += sizeRect / 2.f - size_bullet / 2.f;
			break;
		}

		bullets.emplace_back(pos_bullet, size_bullet, currDir);
		shot_timer.restart();
	}
}

void Tank::setTextureRect()
{
	textureRect.left	= static_cast<int>(currPos.x);
	textureRect.top		= static_cast<int>(currPos.y);
	textureRect.height	= static_cast<int>(sizeRect * 3.f);
	textureRect.width	= static_cast<int>(sizeRect * 3.f);
}

void Tank::setDirection(Direction d)
{
	currDir = d;
	this->rebuild();
}

IntRect& Tank::getTextureRect()
{
	return textureRect;
}

void Tank::drawBullets(RenderWindow& win)
{
	while (!bullets.empty() && (!(bullets.front()).isInWindow(win)))
	{
		bullets.pop_front();
	}

	for (Bullet& b : bullets)
	{
		b.draw_with(win);
	}
}

list<Bullet>& Tank::getBullets()
{
	return bullets;
}