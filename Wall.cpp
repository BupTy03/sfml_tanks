#include "Wall.h"

Wall::Wall(Vector2f p, float sz, bool destr) : destructible(destr)
{
	rect.setPosition(p);
	rect.setSize(Vector2f(sz, sz));
	if (destr)
	{
		rect.setFillColor(Color::Cyan);
	}
	else
	{
		rect.setFillColor(Color(123, 123, 123));
	}
	rect.setOutlineThickness(-sz / 6.f);
	rect.setOutlineColor(Color::Magenta);
	rect.setTextureRect(IntRect(static_cast<int>(p.x), static_cast<int>(p.y), static_cast<int>(sz), static_cast<int>(sz)));
}

bool Wall::isDestructible() const
{
	return destructible;
}

const IntRect& Wall::getTextureRect()
{
	return rect.getTextureRect();
}

void Wall::draw_with(RenderWindow& win)
{ 
	win.draw(rect); 
}