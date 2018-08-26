#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

// направление движения ВПЕРЁД/НАЗАД/ВЛЕВО/ВПРАВО
enum class Direction {
	FRONT, BACK, LEFT, RIGHT
};

using namespace std;
using namespace sf;

class Bullet
{
private:
	RectangleShape rect;
	Direction dir;
	Clock timer;
	void update_texture();

public:
	explicit Bullet(Vector2f p, float sz, Direction dir);
	void make_step();
	void draw_with(RenderWindow& win);
	bool isInWindow(const RenderWindow& win);
	IntRect getTextureRect() const;
};
