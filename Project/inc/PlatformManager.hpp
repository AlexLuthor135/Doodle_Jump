#pragma once

#include "AllHeaders.hpp"

class ManagerContainer;
class GameManager;

class PlatformManager {
private:

	float					_player_width, _player_height;
	float					_platform_width;
	int						_width, _height;
	int						_platforms_passed;
	std::vector<Platform>	_platforms;

public:
	PlatformManager();
	PlatformManager(int width, int height);
	~PlatformManager();
	PlatformManager(const PlatformManager &other);
	PlatformManager &operator=(const PlatformManager &other);
	
	void Tick(ManagerContainer& managers);
	void generatePlatforms(ManagerContainer& managers);
	void createStart(bool &started, float _x, float platform_height);
	void updatePlatforms();
	void calculatePlatforms(GameManager& game_manager);

	void setPlatformGravity(float delta, float delta_time);
	void setFullscreen(int width, int height);
	void resetPlatformsPassed() { _platforms_passed = 0; }

	std::vector<Platform>& getPlatforms() { return _platforms; }
	int getPlatformsPassed() { return _platforms_passed; }

	std::vector<Platform>::iterator erasePlatform(std::vector<Platform>::iterator platformIt);
	void clearPlatforms() { _platforms.clear(); }
};