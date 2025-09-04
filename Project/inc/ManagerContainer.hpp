#include "Managers.hpp"

class ManagerContainer {
    private:
        BulletManager bullet_manager;
        EnemyManager enemy_manager;
        AbilityManager ability_manager;
        PlatformManager platform_manager;
        CollisionManager collision_manager;
        GameManager game_manager;
    
    public:
        ManagerContainer(int width, int height)
            : bullet_manager(width, height),
              enemy_manager(width, height),
              ability_manager(width, height),
              platform_manager(width, height),
              collision_manager(width, height),
              game_manager(width, height) {}
    
        BulletManager& getBulletManager()       { return bullet_manager; }
        EnemyManager& getEnemyManager()         { return enemy_manager; }
        AbilityManager& getAbilityManager()     { return ability_manager; }
        PlatformManager& getPlatformManager()   { return platform_manager; }
        CollisionManager& getCollisionManager() { return collision_manager; }
        GameManager& getGameManager()           { return game_manager; }
    };
    