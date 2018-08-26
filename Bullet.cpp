#include "Bullet.h"

void Bullet::update_texture()
{
	Vector2f p = rect.getPosition();
	float sz = rect.getSize().x;
	rect.setTextureRect(IntRect(static_cast<int>(p.x),
		static_cast<int>(p.y),
		static_cast<int>(sz),
		static_cast<int>(sz)));
}

Bullet::Bullet(Vector2f p, float sz, Direction dir) :dir(dir)
{
	rect.setPosition(p);
	rect.setSize(Vector2f(sz, sz));
	rect.setOutlineThickness(-sz / 6.f);
	rect.setFillColor(Color::Red);
	rect.setOutlineColor(Color::Blue);
	this->update_texture();
}

void Bullet::make_step()
{
	auto pos = rect.getPosition();
	auto sz = rect.getSize().x;
	switch (dir)
	{
	case Direction::FRONT:
		pos.y -= sz;
		break;
	case Direction::BACK:
		pos.y += sz;
		break;
	case Direction::LEFT:
		pos.x -= sz;
		break;
	case Direction::RIGHT:
		pos.x += sz;
		break;
	}
	rect.setPosition(pos);
	this->update_texture();
}

void Bullet::draw_with(RenderWindow& win)
{
	if (timer.getElapsedTime().asSeconds() >= 0.15f)
	{
		make_step();
		timer.restart();
	}
	win.draw(rect);
}

bool Bullet::isInWindow(const RenderWindow& win)
{
	Vector2f posRect = rect.getPosition();

	return
		posRect.x >= 0 &&
		posRect.y >= 0 &&
		posRect.x <= static_cast<float>(win.getSize().x) &&
		posRect.y <= static_cast<float>(win.getSize().y);
}

IntRect Bullet::getTextureRect() const
{
	return rect.getTextureRect();
}