#pragma once

#include "AllHeaders.hpp"

class ManagerContainer;

class GameManager {
private:

	float				_player_width, _player_height;
	float				_platform_width;
	int					_width, _height;
	int					_x, _y;
	int 				_key_left, _key_right;
	int					_direction;
	float				_move_speed;
	float				_delta_time;
	float				_gravity;
	float				_vy;
	float				_max_y;
	float				_initial_y;
	float				_total_distance;

public:
	GameManager();
	GameManager(int width, int height);
	~GameManager();
	GameManager(const GameManager &other);
	GameManager &operator=(const GameManager &other);
	void setDeltaTime(float delta_time) { _delta_time = delta_time;}
	void setKeyLeft(int key_left) { _key_left = key_left; }
	void setKeyRight(int key_right) { _key_right = key_right; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	void setV_Y(float vy) { _vy = vy; }
	void resetTotalDistance() { _total_distance = 0; }

	int getDirection() const { return _direction; }
	int getX() const { return _x; }
	int getY() const { return _y; }
	float& getV_Y() { return _vy; }
	float &getGravity() { return _gravity; }
	float getDistance() { return _total_distance; }

	bool Tick(ManagerContainer& managers);

	void movePlayer();
	bool generateGravity(ManagerContainer& managers);
	void gameReset();
	void setFullscreen(int width, int height);
};