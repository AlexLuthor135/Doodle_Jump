#pragma once

#include "AllHeaders.hpp"
#include "EnemyManager.hpp"
#include "BulletManager.hpp"

class ManagerContainer;

class AbilityManager {
private:

	float				_player_width, _player_height;
	int					_width, _height;
	unsigned int		_ability_spawn_time;
	unsigned int		_ability_cooldown;
	std::vector<Ability> _abilities;

public:
	AbilityManager();
	AbilityManager(int width, int height);
	~AbilityManager();
	AbilityManager(const AbilityManager &other);
	AbilityManager &operator=(const AbilityManager &other);
	
	void Tick(ManagerContainer& managers, unsigned int tick);
	void generateAbility(unsigned int tick);
	void updateAbilities(unsigned int tick);
	void activateAbilities(ManagerContainer& managers, unsigned int tick);
	void activateAutoshoot(Ability& ability, ManagerContainer& managers, unsigned int tick);
	void activateRocket(float &vy);
	void setAbilityGravity(float delta);
	void setFullscreen(int width, int height);

	std::vector<Ability>& getAbilitiess() { return _abilities; }

	std::vector<Ability>::iterator eraseAbility(std::vector<Ability>::iterator abilityIt);
	void clearAbilities() { _abilities.clear(); }
};