#include "../inc/ManagerContainer.hpp"

CollisionManager::CollisionManager(){}

CollisionManager::CollisionManager(int width, int height)
: _width(width), _height(height), _rocket_active(false)
{
	_platform_width     = _width  * 0.1425f;
    _platform_height    = _height * 0.025f;
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
    _jump_impulse       = _height * 2.0f;
}

CollisionManager::~CollisionManager(){}

CollisionManager::CollisionManager(const CollisionManager &other)
: _width(other._width), _height(other._height)
{
    _platform_width     = _width  * 0.1425f;
    _platform_height    = _height * 0.025f;
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
    _jump_impulse       = _height * 2.0f;
}

CollisionManager &CollisionManager::operator=(const CollisionManager &other)
{
    if (this != &other)
    {
        _player_width = other._player_width;
        _player_height = other._player_height;
        _platform_width = other._platform_width;
        _width = other._width;
        _height = other._height;
    }
    return *this;
}

bool CollisionManager::Tick(ManagerContainer &managers, unsigned int tick)
{
    checkBulletEnemyCollisions(managers.getBulletManager(), managers.getEnemyManager());
    checkPlayerPlatformCollisions(managers.getPlatformManager(), managers.getGameManager());
    checkPlayerAbilityCollisions(managers.getAbilityManager(), managers.getGameManager(), tick);
    return checkPlayerEnemyCollisions(managers.getEnemyManager(), managers.getGameManager());
}

void CollisionManager::checkBulletEnemyCollisions(BulletManager& bullet_manager, EnemyManager& enemy_manager)
{
    for (auto bulletIt = bullet_manager.getBullets().begin(); bulletIt != bullet_manager.getBullets().end();)
    {
        bool bulletHit = false;
        for (auto& enemy : enemy_manager.getEnemies())
        {
            if (enemy.alive &&  bulletIt->x < enemy.x + enemy.width && 
                bulletIt->x + (_player_width / 4) > enemy.x &&
                bulletIt->y < enemy.y + enemy.height &&
                bulletIt->y + (_player_height / 4) > enemy.y)
            {
                enemy.alive = false;
                bulletHit = true;
                break;
            }
        }
        if (bulletHit)
            bulletIt = bullet_manager.eraseBullet(bulletIt);
        else
            ++bulletIt;
    }
}

bool CollisionManager::checkPlayerEnemyCollisions(EnemyManager &enemy_manager, GameManager& game_manager)
{
    bool playerFalling = game_manager.getV_Y() < 0;
    for (auto& enemy : enemy_manager.getEnemies())
    {
        if (!enemy.alive)
            continue;

        float collisionWidth = enemy.width * 0.7f;
        float collisionHeight = enemy.height * 0.7f;
        float collisionX = enemy.x + (enemy.width - collisionWidth) / 2;
        float collisionY = enemy.y + (enemy.height - collisionHeight) / 2;

        bool collision = game_manager.getX() < collisionX + collisionWidth &&
                         game_manager.getX() + _player_width > collisionX &&
                         game_manager.getY() < collisionY + collisionHeight &&
                         game_manager.getY() + _player_height > collisionY;
        if (collision)
        {
			if (_rocket_active == true)
			{
				enemy.alive = false;
				return false;
			}
            if (enemy.alive == true && playerFalling)
            {
                enemy.alive = false;
                game_manager.setV_Y(_jump_impulse);
            }
            else
                return true;
        }
    }
    return false;
}

void CollisionManager::checkPlayerPlatformCollisions(PlatformManager &platform_manager, GameManager& game_manager)
{
	bool isFalling = game_manager.getV_Y() < 0;
	for (auto& p : platform_manager.getPlatforms())
    {
        bool hitPlatform = (game_manager.getY() + _player_height >= p.y) && 
                          (game_manager.getY() + _player_height <= p.y + _platform_height) &&
                          (game_manager.getX() + _player_width >= p.x + PLATFORM_MARGIN) && 
                          (game_manager.getX() <= p.x + _platform_width - PLATFORM_MARGIN);

        if (isFalling && hitPlatform)
        {
			if (_rocket_active)
				_rocket_active = false;
            game_manager.setV_Y(_jump_impulse);
            break;
        }
    }
}

void CollisionManager::checkPlayerAbilityCollisions(AbilityManager& ability_manager, GameManager& game_manager, unsigned int tick)
{
    for (auto& ability : ability_manager.getAbilitiess())
    {
        float collisionWidth = ability.width * 0.7f;
        float collisionHeight = ability.height * 0.7f;
        float collisionX = ability.x + (ability.width - collisionWidth) / 2;
        float collisionY = ability.y + (ability.height - collisionHeight) / 2;

        bool collision = game_manager.getX() < collisionX + collisionWidth &&
                         game_manager.getX() + _player_width > collisionX &&
                         game_manager.getY() < collisionY + collisionHeight &&
                         game_manager.getY() + _player_height > collisionY;
        if (collision)
		{
            ability.picked = true;
            ability.used = true;
			ability.time_picked = tick;	
			if (ability.type == ROCKET)
				_rocket_active = true;			
		}
    }
}

void CollisionManager::setFullscreen(int width, int height)
{
    _width = width;
    _height = height;
    _platform_width     = _width  * 0.1425f;
    _platform_height    = _height * 0.025f;
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
    _jump_impulse       = _height * 2.0f;
}