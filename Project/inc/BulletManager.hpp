#pragma once

#include "AllHeaders.hpp"

class BulletManager {
private:

	float				_player_width, _player_height;
	int					_width, _height;
	std::vector<Bullet> _bullets;

public:
	BulletManager();
	BulletManager(int width, int height);
	~BulletManager();
	BulletManager(const BulletManager &other);
	BulletManager &operator=(const BulletManager &other);
	
	void updateBullets();
	void shoot(float target_x, float target_y, float _x, float _y);
	void setBulletGravity(float delta);
	void setFullscreen(int width, int height);

	std::vector<Bullet>& getBullets() { return _bullets; }

	std::vector<Bullet>::iterator eraseBullet(std::vector<Bullet>::iterator bulletIt);
	void clearBullets() { _bullets.clear(); }

};