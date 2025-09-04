#pragma once

#include "AllHeaders.hpp"

class EnemyManager {
private:

	float				_player_width, _player_height;
	float				_platform_width;
	int					_width, _height;
	std::vector<Enemy> _enemies;

public:
	EnemyManager();
	EnemyManager(int width, int height);
	~EnemyManager();
	EnemyManager(const EnemyManager &other);
	EnemyManager &operator=(const EnemyManager &other);
	
	void generateEnemy(Platform platform);

	void updateEnemies();
	void setEnemyGravity(float delta);
	void setFullscreen(int width, int height);

	std::vector<Enemy>& getEnemies() { return _enemies; }

	std::vector<Enemy>::iterator eraseEnemy(std::vector<Enemy>::iterator enemyIt);
	void clearEnemies() { _enemies.clear(); }
};