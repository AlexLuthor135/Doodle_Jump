#include "../inc/ManagerContainer.hpp"

GameManager::GameManager() 
: _width(0), _height(0) {}

GameManager::GameManager(int width, int height) 
: _width(width), _height(height), _key_left(0), _key_right(0), _direction(0), _total_distance(0)
{
	_platform_width     = _width  * 0.1425f;
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
	_move_speed         = _width  * 2.0f;
	_vy                 = _height * 0.083f;
	_gravity            = -_height * 8.0f;
	_x					= _width / 2.0f;
	_y					= _height - _player_height * 3.0f;
	_max_y				= _y;
	_initial_y			= _y;
}

GameManager::~GameManager(){}

GameManager::GameManager(const GameManager &other)
: _width(other._width), _height(other._height)
{
	_platform_width     = _width  * 0.1425f;
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
	_move_speed         = _width  * 2.0f;
	_vy                 = _height * 0.083f;
	_gravity            = -_height * 8.0f;
	_x 					= _width / 2.0f;
	_y 					= _height - _player_height * 1.5f;
	_max_y 				= _y;
	_initial_y 			= _y;
}

GameManager &GameManager::operator=(const GameManager &other)
{
    if (this != &other)
    {
        _width = other._width;
        _height = other._height;
		_platform_width     = _width  * 0.1425f;
		_player_height      = _height * 0.1067f;
		_player_width       = _width  * 0.16f;
		_move_speed         = _width  * 2.0f;
		_vy                 = _height * 0.083f;
		_gravity            = -_height * 8.0f;
		_x					= _width / 2.0f;
		_y					= _height - _player_height * 1.5f;
		_max_y				= _y;
		_initial_y			= _y;
    }
    return *this;
}

bool GameManager::Tick(ManagerContainer& managers)
{
    movePlayer();
    return (generateGravity(managers));
}

void GameManager::movePlayer()
{
	float move_step = _move_speed * _delta_time;
	if (_key_left == 1)
	{
		_direction = 0;
		_x -= move_step;
	}
	if (_key_right == 1)
	{
		_direction = 1;
		_x += move_step;
	}
	if (_x < -_player_width)
		_x = _width;
	else if (_x > _width)
		_x = -_player_width;
}

bool GameManager::generateGravity(ManagerContainer& managers)
{
	float delta = 0.0f;
	
	_vy += _gravity * _delta_time;
	_y -= _vy * _delta_time;

	if (_y > _height)
        return true;
	if (_y < (_height * 0.4f))
	{
		delta = (_height * 0.4f) - _y;
		_y = _height * 0.4f;
		_total_distance += delta;
	}
	managers.getPlatformManager().setPlatformGravity(delta, _delta_time);
	managers.getEnemyManager().setEnemyGravity(delta);
	managers.getBulletManager().setBulletGravity(delta);
	managers.getAbilityManager().setAbilityGravity(delta);
	return false;
}

void GameManager::gameReset()
{
	_vy = _height * 0.083f;
	_max_y = _y;
	_initial_y = _y;
}

void GameManager::setFullscreen(int width, int height)
{
	_width = width;
	_height = height;
	_platform_width     = _width  * 0.1425f;
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
	_move_speed         = _width  * 2.0f;
	_vy                 = _height * 0.083f;
	_gravity            = -_height * 8.0f;
	_x					= _width / 2.0f;
	_y					= _height - _player_height * 3.0f;
	_max_y				= _y;
	_initial_y			= _y;
}