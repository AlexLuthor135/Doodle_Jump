#include "../inc/EnemyManager.hpp"

EnemyManager::EnemyManager()
: _player_width(0), _player_height(0), _platform_width(0), _width(0), _height(0) {}

EnemyManager::EnemyManager(int width, int height) 
:_width(width), _height(height)
{
    _platform_width     = _width  * 0.1425f;
    _player_height      = _height * 0.1067f;
    _player_width       = _width  * 0.16f;
}

EnemyManager::~EnemyManager(){}

EnemyManager::EnemyManager(const EnemyManager &other)
: _width(other._width), _height(other._height), _enemies(other._enemies)
{
    _platform_width     = _width  * 0.1425f;
    _player_height      = _height * 0.1067f;
    _player_width       = _width  * 0.16f;
}

EnemyManager &EnemyManager::operator=(const EnemyManager &other)
{
    if (this != &other)
    {
        _player_width = other._player_width;
        _player_height = other._player_height;
        _platform_width = other._platform_width;
        _width = other._width;
        _height = other._height;
        _enemies = other._enemies;
    }
    return *this;
}

void EnemyManager::generateEnemy(Platform platform)
{
	if (!platform.moving && platform.y < _height * 0.4f &&
		_enemies.size() <= MAX_ENEMIES)
	{
		Enemy e;
		e.width = _player_width;
		e.height = _player_height;
		e.x = platform.x + rand() % static_cast<int>(_platform_width - e.width);
		e.y = platform.y - e.height;
		e.alive = true;
		e.type = rand() % ENEMY_COUNT;
		_enemies.push_back(e);
	}
}

void EnemyManager::updateEnemies()
{
	_enemies.erase(
		std::remove_if(_enemies.begin(), _enemies.end(), [this](const Enemy& e) {
        	return (e.y > _height || !e.alive);
    	}),
		_enemies.end()
	);
}

void EnemyManager::setEnemyGravity(float delta)
{
    for (auto& e : _enemies)
        e.y += delta;
}

void EnemyManager::setFullscreen(int width, int height)
{
    _width = width;
    _height = height;
    _platform_width     = _width  * 0.1425f;
    _player_height      = _height * 0.1067f;
    _player_width       = _width  * 0.16f;
}

std::vector<Enemy>::iterator EnemyManager::eraseEnemy(std::vector<Enemy>::iterator enemyIt)
{
    return _enemies.erase(enemyIt);
}