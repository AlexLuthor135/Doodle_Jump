#include "../inc/ManagerContainer.hpp"

PlatformManager::PlatformManager(){}

PlatformManager::PlatformManager(int width, int height) 
: _width(width), _height(height), _platforms_passed(0)
{
		_platform_width     = _width  * 0.1425f;
		_player_height      = _height * 0.1067f;
		_player_width       = _width  * 0.16f;
}

PlatformManager::~PlatformManager(){}

PlatformManager::PlatformManager(const PlatformManager &other)
: _width(other._width), _height(other._height), _platforms(other._platforms)
{
	_platform_width     = _width  * 0.1425f;
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
}

PlatformManager &PlatformManager::operator=(const PlatformManager &other)
{
    if (this != &other)
    {
        _player_width = other._player_width;
        _player_height = other._player_height;
        _platform_width = other._platform_width;
        _width = other._width;
        _height = other._height;
        _platforms = other._platforms;
    }
    return *this;
}

void PlatformManager::Tick(ManagerContainer& managers)
{
	generatePlatforms(managers);
	calculatePlatforms(managers.getGameManager());
}

void PlatformManager::generatePlatforms(ManagerContainer& managers)
{
	float jump_height = (managers.getCollisionManager().getJumpImpulse() * managers.getCollisionManager().getJumpImpulse() / (-2.0f * managers.getGameManager().getGravity()));
	_platforms.erase(
		std::remove_if(_platforms.begin(), _platforms.end(), [this](const Platform& p) {
			return p.y > _height;
		}),
		_platforms.end()
	);
	
	float topY = _height;
	for (const auto& p : _platforms)
	{
		if (p.y < topY)
			topY = p.y;
	}
	while (_platforms.size() < MAX_PLATFORMS)
	{
		Platform platform;
		platform.x = rand() % static_cast<int>(_width - _platform_width);
		platform.y = topY - (rand() % static_cast<int>((jump_height)));
		platform.passed = false;
		platform.moving = false;
		platform.start_y = platform.y;
		platform.move_direction = 1;
		platform.move_range = jump_height;
		platform.move_speed = _height * 0.2f;
		if (rand() % 100 < 10)
			platform.moving = true;
		_platforms.push_back(platform);
		if (rand () % 100 < 15)
			managers.getEnemyManager().generateEnemy(platform);
		topY = platform.y;
	}
}

void PlatformManager::createStart(bool &started, float _x, float platform_height)
{
    Platform platform;
	platform.x = _x;
	platform.y = _height - (platform_height);
	_platforms.push_back(platform);
	started = true;
}

void PlatformManager::updatePlatforms()
{
	_platforms.erase(
		std::remove_if(_platforms.begin(), _platforms.end(), [this](const Platform& p) {
			return p.y > _height;
		}),
		_platforms.end()
	);
}

void PlatformManager::setPlatformGravity(float delta, float delta_time)
{
    for (auto& p : _platforms)
	{
		p.y += delta;
		p.start_y += delta;
		if (p.moving)
		{
			float move_step = p.move_speed * delta_time;
			if (p.move_direction == 1)
			{
				p.y -= move_step;
				if (p.y < p.start_y - p.move_range)
					p.move_direction = 0;
			}
			else
			{
				p.y += move_step;
				if (p.y > p.start_y)
					p.move_direction = 1;
			}
		}
	}
}

void PlatformManager::calculatePlatforms(GameManager& game_manager)
{
	for (auto p = _platforms.begin(); p != _platforms.end(); p++)
	{
		if (!p->passed && (game_manager.getY() + _player_height) < p->y)
        {
            p->passed = true;
            _platforms_passed++;
        }
	}
}

void PlatformManager::setFullscreen(int width, int height)
{
	_width = width;
	_height = height;
	_platform_width     = _width  * 0.1425f;
		_player_height  = _height * 0.1067f;
		_player_width   = _width  * 0.16f;
}


std::vector<Platform>::iterator PlatformManager::erasePlatform(std::vector<Platform>::iterator platformIt)
{
    return _platforms.erase(platformIt);
}