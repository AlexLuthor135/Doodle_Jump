#pragma once

#include "AllHeaders.hpp"

class ManagerContainer;

class CollisionManager {
private:
	float	_player_width, _player_height;
	float	_platform_width, _platform_height;
	float	_jump_impulse;
	int		_width, _height;
	bool	_rocket_active;

public:
	CollisionManager();
	CollisionManager(int width, int height);
	~CollisionManager();
	CollisionManager(const CollisionManager &other);
	CollisionManager &operator=(const CollisionManager &other);

	bool Tick(ManagerContainer& managers, unsigned int tick);
	void checkBulletEnemyCollisions(BulletManager& bullet_manager, EnemyManager& enemy_manager);
	bool checkPlayerEnemyCollisions(EnemyManager &enemy_manager, GameManager& game_manager);
	void checkPlayerPlatformCollisions(PlatformManager &platform_manager, GameManager& game_manager);
	void checkPlayerAbilityCollisions(AbilityManager& ability_manager, GameManager& game_manager, unsigned int tick);
	void setFullscreen(int width, int height);

	float& getJumpImpulse() { return _jump_impulse; }
	bool& getRocketActive() { return _rocket_active; }
};