#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <filesystem>
#include <fstream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "Tank.h"
#include "EnemyTank.h"
#include "Wall.h"
#include "SMatrix.h"

using namespace std;
using namespace sf;

class GameMap
{
private:
	list<Wall> walls;
	Tank main_tank;
	list<EnemyTank> enemies;
	const float item_size;
	const int map_size;
	void delEnemiesAndWallsAndBullets();

public:
	GameMap(float itsz, int mpsz) : item_size(itsz), map_size(mpsz) {}

	// строит карту по двумерному массиву bool
	template<const Index SizeMap>
	void buildMap(const SMatrix<bool, SizeMap, SizeMap>& matrix, bool dest)
	{
		for (Index i = 0; i < SizeMap; ++i){
			for (Index j = 0; j < SizeMap; ++j){
				if (matrix[i][j]){
					addWall(i, j, dest);
				}
			}
		}
	}

	void drawWallsWith(RenderWindow& win);
	void addWall(int i, int j, bool d);

	void emplaceMainTank(Vector2f pos, float sizeR, Direction dir, Color col);
	void updateMainTank(Direction dir, bool shot);
	void drawMainTankWith(RenderWindow& win);
	Tank& getMainTank();

	void emplaceEnemy(Vector2f pos, float sizeR, Direction dir, Color col = Color::Red);
	void drawEnemiesWith(RenderWindow& win);
	list<EnemyTank>& getEnemies();

	// просчитывает логику игры:
	// удаляет столкнувшиеся элементы,
	// определяет проигрыш/выигрыш
	bool computeLogic();

	void drawAllWith(RenderWindow& win);

	bool ParseFromFile(filesystem::path& filename);
};

