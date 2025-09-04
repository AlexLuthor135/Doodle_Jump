#ifndef ALL_HEADERS_HPP
# define ALL_HEADERS_HPP

# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <ctime>
# include <array>
# include <cmath>
# include <memory>
# include <regex>

constexpr float			PLATFORM_MARGIN = 16.0f;
const int				MAX_PLATFORMS = 30;
const int				MAX_ENEMIES = 30;
const int               MAX_ABILITIES = 1;
constexpr const char*	PLAYER_LEFT_SPRITE = "../data/jungle-left.png";
constexpr const char*	PLAYER_RIGHT_SPRITE = "../data/jungle-right.png";
constexpr const char*	PLATFORM_SPRITE    = "../data/platform.png";
constexpr const char*	BACKGROUND_SPRITE  = "../data/background.png";
constexpr const char*	SCORE_BAR_SPRITE = "../data/score_bar.png";
constexpr const char*	BULLET_SPRITE = "../data/bullet.png";
constexpr const char*   PLAY_BUTTON = "../data/play.png";
constexpr const char*   PLAY_AGAIN_BUTTON = "../data/play_again.png";
constexpr const char*   MENU_BUTTON = "../data/menu.png";
constexpr const char*   LEFT_ARROW = "../data/left_arrow.png";
constexpr const char*   RIGHT_ARROW = "../data/right_arrow.png";

enum DigitSprite {
    DIGIT_0 = 0,
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4,
    DIGIT_5,
    DIGIT_6,
    DIGIT_7,
    DIGIT_8,
    DIGIT_9,
    DIGIT_COUNT
};

enum PlayerLeftSprite {
    PLAYERLEFT_0 = 0,
    PLAYERLEFT_1,
    PLAYERLEFT_2,
    PLAYERLEFT_3,
    PLAYERLEFT_4,
    PLAYERLEFT_5,
    PLAYERLEFT_6,
    PLAYERLEFT_7,
    PLAYERLEFT_8,
    PLAYERLEFT_9,
    PLAYERLEFT_COUNT
};

enum PlayerRightSprite {
    PLAYERRIGHT_0 = 0,
    PLAYERRIGHT_1,
    PLAYERRIGHT_2,
    PLAYERRIGHT_3,
    PLAYERRIGHT_4,
    PLAYERRIGHT_5,
    PLAYERRIGHT_6,
    PLAYERRIGHT_7,
    PLAYERRIGHT_8,
    PLAYERRIGHT_9,
    PLAYERRIGHT_COUNT
};

enum EnemySprite {
    ENEMY_0 = 0,
    ENEMY_1,
    ENEMY_2,
    ENEMY_COUNT
};

enum AbilitySprite {
    ABILITY_0 = 0,
    ABILITY_2,
    ABILITY_COUNT
};

enum GameState{
    MENU = 0,
    GAME,
    ENDGAME,
    STATE_COUNT,
};

constexpr std::array<const char*, DIGIT_COUNT> DIGIT_PATHS = {
    "../data/0.png",
    "../data/1.png",
    "../data/2.png",
    "../data/3.png",
    "../data/4.png",
    "../data/5.png",
    "../data/6.png",
    "../data/7.png",
    "../data/8.png",
    "../data/9.png"
};

constexpr std::array<const char*, PLAYERLEFT_COUNT> PLAYERLEFT_PATHS = {
    "../data/blue-lik-left.png",
    "../data/bunny-left.png",
    "../data/doodlestein-left.png",
    "../data/frozen-left.png",
    "../data/ghost-left.png",
    "../data/ice-left.png",
    "../data/jungle-left.png",
    "../data/soccer-left.png",
    "../data/space-left.png",
    "../data/underwater-left.png"
};

constexpr std::array<const char*, PLAYERRIGHT_COUNT> PLAYERRIGHT_PATHS = {
    "../data/blue-lik-right.png",
    "../data/bunny-right.png",
    "../data/doodlestein-right.png",
    "../data/frozen-right.png",
    "../data/ghost-right.png",
    "../data/ice-right.png",
    "../data/jungle-right.png",
    "../data/soccer-right.png",
    "../data/space-right.png",
    "../data/underwater-right.png"
};

constexpr std::array<const char*, ENEMY_COUNT> ENEMY_PATHS = {
    "../data/enemy_0.png",
    "../data/enemy_1.png",
    "../data/enemy_2.png",
};

constexpr std::array<const char*, ABILITY_COUNT> ABILITY_PATHS = {
    "../data/ability_autoshoot.png",
    "../data/ability_rocket.png",
};

struct Platform {
    float	x, y;
    bool	passed;
    bool	moving;
    float	move_speed;
    int		move_direction;
    float	move_range;
    float	start_y;
};

struct Enemy {
    float x, y;
    float width, height;
    int type;
    bool alive;
};

struct Bullet {
    float x, y;
    float vx, vy;
};

enum AbilityType{
	AUTOSHOOT = 0,
	ROCKET,
	ABILITY_TYPE_COUNT,
};

struct Ability {
    float			x, y;
    float 			width, height;
    float			duration;
    bool			picked;
    bool            used;
    AbilityType 	type;
    unsigned int	time_picked;
    unsigned int	lastAutoshootTime;
};

#endif
