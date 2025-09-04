#include "../inc/ManagerContainer.hpp"

AbilityManager::AbilityManager() 
: _player_width(0), _player_height(0), _width(0), _height(0), _ability_spawn_time(0), _ability_cooldown(0) {}

AbilityManager::AbilityManager(int width, int height) 
: _width(width), _height(height), _ability_spawn_time(0)
{
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
	_ability_cooldown	= rand() % 30 + 5;
}

AbilityManager::~AbilityManager(){}

AbilityManager::AbilityManager(const AbilityManager &other)
: _width(other._width), _height(other._height), _ability_spawn_time(other._ability_spawn_time), _ability_cooldown(other._ability_cooldown), _abilities(other._abilities)
{
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
}

AbilityManager &AbilityManager::operator=(const AbilityManager &other)
{
    if (this != &other)
    {
        _player_width = other._player_width;
        _player_height = other._player_height;
        _width = other._width;
        _height = other._height;
        _ability_spawn_time = other._ability_spawn_time;
        _ability_cooldown = other._ability_cooldown;
        _abilities = other._abilities;
    }
    return *this;
}

void AbilityManager::Tick(ManagerContainer &managers, unsigned int tick)
{
	updateAbilities(tick);
	generateAbility(tick);
	activateAbilities(managers, tick);
}

void AbilityManager::generateAbility(unsigned int tick)
{
	if (tick - _ability_spawn_time >= _ability_cooldown)
    {
		if (_abilities.size() < MAX_ABILITIES)
		{
			Ability a;
			a.width = _player_width;
			a.height = _player_height;
			a.x = rand() % static_cast<int>(_width - a.width);
    	    a.y = rand() % static_cast<int>(_height - a.height);
			a.type = static_cast<AbilityType>(rand() % ABILITY_TYPE_COUNT);
			a.picked = false;
			a.used = false;
			if (a.type == ROCKET)
				a.duration = 2.0f;
			else if (a.type == AUTOSHOOT)
			{
				a.duration = 20.0f;
				a.lastAutoshootTime = tick;
			}
			_abilities.push_back(a);
			_ability_spawn_time = tick;
			_ability_cooldown = rand() % 30 + 5;
		}
	}
}

void AbilityManager::updateAbilities(unsigned int tick)
{
    _abilities.erase(
		std::remove_if(_abilities.begin(), _abilities.end(), [this](const Ability& a) {
        	return (a.y > _height && !a.picked) || (!a.picked && a.used);
    	}),
		_abilities.end()
	);
	for (auto it = _abilities.begin(); it != _abilities.end();)
	{
		if (it->picked == true)
		{
			float elapsedTime = (tick - it->time_picked);
			if (elapsedTime >= it->duration)
				it->picked = false;
		}
		++it;
	}
}

void AbilityManager::activateAbilities(ManagerContainer& managers, unsigned int tick)
{
	for (auto& ability : _abilities)
	{
		if (ability.picked)
		{
			if (ability.type == ROCKET)
				activateRocket(managers.getGameManager().getV_Y());
			else if (ability.type == AUTOSHOOT)
				activateAutoshoot(ability, managers, tick);
		}
	}
}

void AbilityManager::activateRocket(float &vy)
{
	vy = _height * 4.0f;
}

void AbilityManager::activateAutoshoot(Ability& ability, ManagerContainer& managers, unsigned int tick)
{
    float elapsedTime = (tick - ability.lastAutoshootTime);
    if (elapsedTime >= 0.5f)
    {
        for (auto& enemy : managers.getEnemyManager().getEnemies())
        {
            if (enemy.y > 0 && enemy.y < _height)
            {
				managers.getBulletManager().shoot(enemy.x, enemy.y, managers.getGameManager().getX(), managers.getGameManager().getY());
				ability.lastAutoshootTime = tick;
				return ;
			}    
        }
    }
}

void AbilityManager::setAbilityGravity(float delta)
{
    for (auto& a : _abilities)
        a.y += delta;
}

void AbilityManager::setFullscreen(int width, int height)
{
	_width = width;
	_height = height;
	_player_height	= _height * 0.1067f;
	_player_width	= _width  * 0.16f;
}

std::vector<Ability>::iterator AbilityManager::eraseAbility(std::vector<Ability>::iterator abilityIt)
{
    return _abilities.erase(abilityIt);
}