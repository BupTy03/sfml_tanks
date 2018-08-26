#include "GameMap.h"

using namespace std;

void GameMap::delEnemiesAndWallsAndBullets()
{
	// находим и сохраняем итераторы объектов, которые нужно удалить
	// после их столкновения друг с другом
	list<list<Bullet>::iterator> MyBulletsItToDel;
	list<list<EnemyTank>::iterator> EnemiesItToDel;
	list<list<Wall>::iterator> WallsToDel;

	for (auto WIt = begin(walls), WItE = end(walls); WIt != WItE; ++WIt)
	{
		for (auto BIt = begin(main_tank.getBullets()), BItE = end(main_tank.getBullets()); BIt != BItE; ++BIt)
		{
			if ((BIt->getTextureRect()).intersects(WIt->getTextureRect()))
			{
				MyBulletsItToDel.push_back(BIt);
				if (WIt->isDestructible())
				{
					WallsToDel.push_back(WIt);
				}
			}

			for (auto EIt = begin(enemies), EItE = end(enemies); EIt != EItE; ++EIt)
			{
				if ((EIt->getTextureRect()).intersects(BIt->getTextureRect()))
				{
					EnemiesItToDel.push_back(EIt);
					MyBulletsItToDel.push_back(BIt);
				}

				for (auto BulEIt = begin(EIt->getBullets()), BulEItE = end(EIt->getBullets()); BulEIt != BulEItE; ++BulEIt)
				{
					if (WIt->isDestructible() && (BulEIt->getTextureRect()).intersects(WIt->getTextureRect()))
					{
						WallsToDel.push_back(WIt);
					}
				}
			}
		}

		for (auto EIt = begin(enemies), EItE = end(enemies); EIt != EItE; ++EIt)
		{
			for (auto BulEIt = begin(EIt->getBullets()), BulEItE = end(EIt->getBullets()); BulEIt != BulEItE; ++BulEIt)
			{
				if (WIt->isDestructible() && (BulEIt->getTextureRect()).intersects(WIt->getTextureRect()))
				{
					WallsToDel.push_back(WIt);
				}
			}
		}
	}

	// устраняем дубликаты

	MyBulletsItToDel.erase(unique(begin(MyBulletsItToDel), end(MyBulletsItToDel)), end(MyBulletsItToDel));
	EnemiesItToDel.erase(unique(begin(EnemiesItToDel), end(EnemiesItToDel)), end(EnemiesItToDel));
	WallsToDel.erase(unique(begin(WallsToDel), end(WallsToDel)), end(WallsToDel));

	// удаляем объекты

	for (auto& it : MyBulletsItToDel)
	{
		(main_tank.getBullets()).erase(it);
	}

	list<Wall>& ref_to_walls = walls;
	for (auto& enemy : enemies)
	{
		list<Bullet>& ref_EnB = enemy.getBullets();
		ref_EnB.erase(remove_if(begin(ref_EnB), end(ref_EnB), [&ref_to_walls](Bullet& b)
		{
			for (auto& w_it : ref_to_walls)
			{
				if ((w_it.getTextureRect()).intersects(b.getTextureRect()))
				{
					return true;
				}
			}
			return false;
		}), end(ref_EnB));
	}

	for (auto& it : EnemiesItToDel)
	{
		enemies.erase(it);
	}

	for (auto& it : WallsToDel)
	{
		walls.erase(it);
	}
}

void GameMap::drawWallsWith(RenderWindow& win)
{
	for (Wall& w : walls)
	{
		w.draw_with(win);
	}
}

void GameMap::addWall(int i, int j, bool d)
{
	if (i < 0 || j < 0 || i > map_size || j > map_size){
		throw runtime_error{ "invalid addWall: i or j index are out of GameMap" };
	}
	walls.emplace_back(Vector2f(i*item_size, j*item_size), item_size, d);
}

void GameMap::emplaceMainTank(Vector2f pos, float sizeR, Direction dir, Color col)
{
	main_tank = Tank(pos, sizeR, dir, col);
}

void GameMap::updateMainTank(Direction dir, bool shot)
{
	if (shot) 
	{
		main_tank.make_shot();
	}
	main_tank.setDirection(dir);
}

void GameMap::drawMainTankWith(RenderWindow& win)
{
	main_tank.draw_with(win);
}

void GameMap::drawAllWith(RenderWindow& win)
{
	this->drawWallsWith(win);
	this->drawMainTankWith(win);
	this->drawEnemiesWith(win);
}

bool GameMap::ParseFromFile(filesystem::path& filename)
{
	ifstream ifs(filename, ios_base::in);

	if (!ifs.is_open())
	{
		return false;
	}

	string line;
	for (int i = 0; i < this->map_size && getline(ifs, line); ++i)
	{
		if (line.length() > this->map_size)
		{
			return false;
		}

		for (int j = 0; j < line.length(); ++j)
		{
			switch (line[j])
			{
			case '*':
				this->addWall(j, i, true);
				break;
			case '#':
				this->addWall(j, i, false);
				break;
			default:
				break;
			}
		}
	}
	return true;
}

Tank& GameMap::getMainTank()
{
	return main_tank;
}

void GameMap::emplaceEnemy(Vector2f pos, float sizeR, Direction dir, Color col)
{
	enemies.emplace_back(pos, sizeR, dir, col);
}

void GameMap::drawEnemiesWith(RenderWindow & win)
{
	for (EnemyTank& et : enemies)
	{
		et.draw_with(win);
	}
}

list<EnemyTank>& GameMap::getEnemies()
{
	return enemies;
}

bool GameMap::computeLogic()
{
	IntRect rectMainTank = main_tank.getTextureRect();


	for (Wall& w : walls)
	{
		if (rectMainTank.intersects(w.getTextureRect()))
		{
			return false;
		}
	}

	for (EnemyTank& et : enemies) 
	{
		if (rectMainTank.intersects(et.getTextureRect())) 
		{
			return false;
		}

		for (Bullet& enb : et.getBullets())
		{
			if (rectMainTank.intersects(enb.getTextureRect()))
			{
				return false;
			}
		}
	}

	delEnemiesAndWallsAndBullets();

	return true;
}
