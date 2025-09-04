#include "../inc/BulletManager.hpp"

BulletManager::BulletManager() 
: _player_width(0), _player_height(0), _width(0), _height(0) {}

BulletManager::BulletManager(int width, int height) 
: _width(width), _height(height)
{
    _player_height      = _height * 0.1067f;
    _player_width       = _width  * 0.16f;
}

BulletManager::~BulletManager(){}

BulletManager::BulletManager(const BulletManager &other)
: _width(other._width), _height(other._height), _bullets(other._bullets)
{
    _player_height      = _height * 0.1067f;
    _player_width       = _width  * 0.16f;
}

BulletManager &BulletManager::operator=(const BulletManager &other)
{
    if (this != &other)
    {
        _player_width = other._player_width;
        _player_height = other._player_height;
        _width = other._width;
        _height = other._height;
        _bullets = other._bullets;
    }
    return *this;
}

void BulletManager::shoot(float target_x, float target_y, float _x, float _y)
{
	Bullet bullet;

	bullet.x = _x + _player_width / 2.0f;
	bullet.y = _y + _player_height / 2.0f;

	float dx = target_x - bullet.x;
	float dy = target_y - bullet.y;
	float length = std::sqrt(dx * dx + dy * dy);
	float speed = 0.003f * _height;

	if (length != 0)
    {
        bullet.vx = dx / length * speed;
        bullet.vy = dy / length * speed;
    }
    else
    {
        bullet.vx = 0;
        bullet.vy = -speed;
    }
    _bullets.push_back(bullet);
}

void BulletManager::updateBullets()
{
	if (_bullets.size() > 0)
	{
		for (auto& b : _bullets)
		{
			b.x += b.vx;
			b.y += b.vy;
			if (b.x < -_player_width / 4)
                b.x = _width;
            else if (b.x > _width)
                b.x = -_player_width / 4;
		}
		_bullets.erase(
			std::remove_if(_bullets.begin(), _bullets.end(), [this](const Bullet& b) {
				return b.y < 0 || b.y > _height;
			}),
			_bullets.end()
		);
	}
}

void BulletManager::setBulletGravity(float delta)
{
    for (auto& b : _bullets)
        b.y += delta;
}


void BulletManager::setFullscreen(int width, int height)
{
    _width = width;
    _height = height;
    _player_height      = _height * 0.1067f;
    _player_width       = _width  * 0.16f;
}

std::vector<Bullet>::iterator BulletManager::eraseBullet(std::vector<Bullet>::iterator bulletIt)
{
    return _bullets.erase(bulletIt);
}