#include "../inc/GameEngine.hpp"

GameEngine::GameEngine(int height, int width, bool fullscreen) : _width(width), _height(height), _score_bar_height(36), _mouse_x(0.0f), _mouse_y(0.0f), _started(false),
_game_state(MENU), _lives(5), _costume_id(0), _fullscreen(fullscreen), _last_tick(0), _delta_time(0.0f), _managers(width, height)
	{
	initValues();
	init();
}

GameEngine::~GameEngine()
{
	SDL_DestroyRenderer(getRenderer());
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

GameEngine::GameEngine(const GameEngine &other) : _width(other._width), _height(other._height), _digit_dimensions(other._digit_dimensions), _digit_size(other._digit_size),
	_score_bar_height(other._score_bar_height), _mouse_x(other._mouse_x), _mouse_y(other._mouse_y), _started(other._started), _game_state(other._game_state), _button_x(other._button_x),
	_play_button_y(other._play_button_y), _menu_button_y(other._menu_button_y), _button_width(other._button_width), _button_height(other._button_height), _arrow_size(other._arrow_size),
	_arrow_left_x(other._arrow_left_x), _arrow_right_x(other._arrow_right_x), _arrow_y(other._arrow_y), _lives(other._lives), _costume_id(other._costume_id), _fullscreen(other._fullscreen), _managers(other._managers)
{
	initValues();
	init();
}

GameEngine &GameEngine::operator=(const GameEngine &other)
{
	if (this != &other)
	{
		_width = other._width;
		_height = other._height;
		_digit_dimensions = other._digit_dimensions;
		_digit_size = other._digit_size;
		_score_bar_height = other._score_bar_height;
		_mouse_x = other._mouse_x;
		_mouse_y = other._mouse_y;
		_started = other._started;
		_game_state = other._game_state;
		_button_x = other._button_x;
		_play_button_y = other._play_button_y;
		_menu_button_y = other._menu_button_y;
		_button_width = other._button_width;
		_button_height = other._button_height;
		_arrow_size = other._arrow_size;
		_arrow_left_x = other._arrow_left_x;
		_arrow_right_x = other._arrow_right_x;
		_arrow_y = other._arrow_y;
		_lives = other._lives;
		_costume_id = other._costume_id;
		_fullscreen = other._fullscreen;
		_managers = other._managers;
		destroyTextures();
		createTextures();
	}
	return *this;
}

void GameEngine::PreInit(int& width, int& height, bool& fullscreen)
{
	fullscreen = _fullscreen;
	width = _width;
	height = _height;
}

bool GameEngine::init()
{
	std::srand(std::time(NULL));
	if (!SDL_Init(SDL_INIT_VIDEO)) 
	{
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		throw std::runtime_error("Runtime error SDL_Init thrown from GameEngine constructor");
    }
	_window = SDL_CreateWindow(GetTitle(), _width, _height, SDL_WINDOW_OPENGL);
	if (_window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s", SDL_GetError());
		throw std::runtime_error("Runtime error CreateWindow thrown from GameEngine constructor");
	}
	setRenderer(SDL_CreateRenderer(_window, NULL));
	createTextures();

	bool done = false;
	while (!done)
	{
	    SDL_Event e;
	    while (SDL_PollEvent(&e))
	    {
	        switch (e.type)
	        {
	        case SDL_EVENT_QUIT:
	            done = true;
	            break;
	        case SDL_EVENT_MOUSE_MOTION:
	            onMouseMove(e.motion.x, e.motion.y,
	                        e.motion.xrel, e.motion.yrel);
	            break;

	        case SDL_EVENT_MOUSE_BUTTON_DOWN:
	            onMouseButtonClick(MouseButton::LEFT, false);
	            break;

	        case SDL_EVENT_MOUSE_BUTTON_UP:
	            onMouseButtonClick(MouseButton::LEFT, true);
	            break;

	        case SDL_EVENT_KEY_DOWN:
	            switch (e.key.key)
	            {
				case SDLK_ESCAPE: done = true; break;
	            case SDLK_LEFT:  onKeyPressed(Key::LEFT);  break;
	            case SDLK_RIGHT: onKeyPressed(Key::RIGHT); break;
	            default: break;
	            }
	            break;

	        case SDL_EVENT_KEY_UP:
	            switch (e.key.key)
	            {
	            case SDLK_LEFT:  onKeyReleased(Key::LEFT);  break;
	            case SDLK_RIGHT: onKeyReleased(Key::RIGHT); break;
	            default: break;
	            }
	            break;
	        }
	    }
	    SDL_RenderClear(_renderer);
	    Tick();
	    SDL_RenderPresent(_renderer);
	}
	return true;
}

void GameEngine::Close()
{
	destroyTextures();
}

bool GameEngine::Tick()
{
	generateTimeDelta();
	setFullscreen();
	if (_game_state == MENU)
		MenuView();
	else if (_game_state == ENDGAME)
		EndGameView();
	else if (_game_state == GAME)
		GameView();
	return false;
}

void GameEngine::MenuView()
{
	drawMenuSprites();
}

void GameEngine::EndGameView()
{
	drawEndGameSprites();
}

void GameEngine::GameView()
{
	if (_started == false)
		createStart();
	_managers.getGameManager().setDeltaTime(_delta_time);
	drawGameSprites();
	_managers.getBulletManager().updateBullets();
	_managers.getEnemyManager().updateEnemies();
	_managers.getPlatformManager().Tick(_managers);
	_managers.getAbilityManager().Tick(_managers, SDL_GetTicks() / 1000);
	if (_managers.getGameManager().Tick(_managers) ||
		_managers.getCollisionManager().Tick(_managers, SDL_GetTicks() / 1000))
		endGame();
}

void GameEngine::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	_mouse_x = x;
	_mouse_y = y;
	(void)xrelative;
	(void)yrelative;
}

void GameEngine::onMouseButtonClick(MouseButton button, bool isReleased)
{
	if (button == MouseButton::LEFT && !isReleased)
	{
		if (_game_state == GAME)
		_managers.getBulletManager().shoot(_mouse_x, _mouse_y, _managers.getGameManager().getX(), _managers.getGameManager().getY());
		else if (_game_state == MENU)
		{	
			if (getMouseButtonClick(_play_button, _button_x, _play_button_y))
				_game_state = GAME;
		}
		else if (_game_state == ENDGAME)
		{
			if (getMouseButtonClick(_play_again_button, _button_x, _play_button_y))
			{
				_managers.getPlatformManager().resetPlatformsPassed();
				_managers.getGameManager().resetTotalDistance();
				_game_state = GAME;
			}
			if (getMouseButtonClick(_menu_button, _button_x, _menu_button_y))
			{
				_managers.getPlatformManager().resetPlatformsPassed();
				_managers.getGameManager().resetTotalDistance();
				_game_state = MENU;
			}
		}
	}
}

bool GameEngine::getMouseButtonClick(const Texture& tex, int x, int y) const
{
    return _mouse_x >= x && _mouse_x <= x + tex.w &&
           _mouse_y >= y && _mouse_y <= y + tex.h;
}

void GameEngine::onKeyPressed(Key k)
{
	if (_game_state == GAME)
	{
		switch (k) {
			case Key::LEFT:
				_managers.getGameManager().setKeyLeft(1);
				break;
			case Key::RIGHT:
				_managers.getGameManager().setKeyRight(1);
				break;
			default:
				break;	
		}
	}
	if (_game_state == MENU)
	{
		switch (k) {
			case Key::LEFT:
				_costume_id = (_costume_id - 1 + PLAYERLEFT_COUNT) % PLAYERLEFT_COUNT;
				break;
			case Key::RIGHT:
				_costume_id = (_costume_id + 1) % PLAYERLEFT_COUNT;
				break;
			default:
				break;
		}
	}
}

void GameEngine::onKeyReleased(Key k)
{
	if (_game_state == GAME)
		{
		switch (k) {
			case Key::LEFT:
				_managers.getGameManager().setKeyLeft(0);
				break;
			case Key::RIGHT:
				_managers.getGameManager().setKeyRight(0);
				break;
			default:
				break;
		}
	}
}

void GameEngine::initValues()
{
	_digit_dimensions   = _width  * 0.05f;
	_score_bar_height   = _height * 0.06f;
	_platform_height    = _height * 0.025f;
	_platform_width     = _width  * 0.1425f;
	_player_height      = _height * 0.1067f;
	_player_width       = _width  * 0.16f;
	_button_width  		= _width * 0.2f;
	_button_height 		= _height * 0.1f;
	_button_x			= (_width - _button_width) / 2.0f;
	_play_button_y		= _height / 8;
	_menu_button_y		= _height * 0.8f;
	_arrow_size 		= _height * 0.08f;
	_arrow_y 			= _height / 2.0f;
	_arrow_left_x 		= _width * 0.2f;
	_arrow_right_x 		= _width * 0.6f;
}

void GameEngine::createTextures()
{
	_platform = { loadTexture(PLATFORM_SPRITE), _platform_width, _platform_height };
	_background = { loadTexture(BACKGROUND_SPRITE), (float)_width, (float)_height };
	_score_bar = { loadTexture(SCORE_BAR_SPRITE), (float)_width, _score_bar_height };
	_bullet = { loadTexture(BULLET_SPRITE), _player_width / 4, _player_height / 4 };
	_play_button = { loadTexture(PLAY_BUTTON), _button_width, _button_height };
	_play_again_button = { loadTexture(PLAY_AGAIN_BUTTON), _button_width, _button_height };
	_menu_button = { loadTexture(MENU_BUTTON), _button_width, _button_height };
	_left_arrow = { loadTexture(LEFT_ARROW), _arrow_size, _arrow_size };
	_right_arrow = { loadTexture(RIGHT_ARROW), _arrow_size, _arrow_size };
	for (int i = 0; i < PLAYERLEFT_COUNT; ++i)
		_playerleft_sprites[i] = { loadTexture(PLAYERLEFT_PATHS[i]), _player_width, _player_height };
	for (int i = 0; i < PLAYERRIGHT_COUNT; ++i)
		_playerright_sprites[i] = { loadTexture(PLAYERRIGHT_PATHS[i]), _player_width, _player_height };
	for (int i = 0; i < DIGIT_COUNT; ++i)
		_digit_sprites[i] = { loadTexture(DIGIT_PATHS[i]), _digit_dimensions, _digit_dimensions };
	for (int i = 0; i < ENEMY_COUNT; ++i)
		_enemy_sprites[i] = { loadTexture(ENEMY_PATHS[i]), _player_width * 0.8f, _player_height * 0.8f };
	for (int i = 0; i < ABILITY_COUNT; ++i)
		_ability_sprites[i] = { loadTexture(ABILITY_PATHS[i]), _player_width * 0.8f, _player_height * 0.8f };
}

void GameEngine::drawGameSprites()
{
	drawTexture(_background, 0, 0);
	if (_managers.getGameManager().getDirection() == 0)
		drawTexture(_playerleft_sprites[_costume_id], _managers.getGameManager().getX() , _managers.getGameManager().getY());
	else
		drawTexture(_playerright_sprites[_costume_id], _managers.getGameManager().getX() , _managers.getGameManager().getY());
	for (auto& p : _managers.getPlatformManager().getPlatforms())
		drawTexture(_platform, p.x, p.y);
	for (const auto& b : _managers.getBulletManager().getBullets())
        drawTexture(_bullet, b.x, b.y);
	for (const auto& enemy : _managers.getEnemyManager().getEnemies())
		if (enemy.type >= 0 && enemy.type < ENEMY_COUNT)
			drawTexture(_enemy_sprites[enemy.type], enemy.x, enemy.y);
	for (const auto& ability : _managers.getAbilityManager().getAbilitiess())
		if (ability.picked == false && ability.type >= 0 && ability.type < ABILITY_TYPE_COUNT)
			drawTexture(_ability_sprites[ability.type], ability.x, ability.y);
	drawTexture(_score_bar, 0, 0);
	drawNumber(_managers.getPlatformManager().getPlatformsPassed(), 0, 0);
	drawNumber(_managers.getGameManager().getDistance(), _width / 3, 0);
	drawNumber(_lives, _width - _digit_dimensions, 0);
}

void GameEngine::drawMenuSprites()
{
	drawTexture(_background, 0, 0);
	drawTexture(_play_button, _button_x, _play_button_y);
	drawTexture(_playerleft_sprites[_costume_id], _width / 2.0f - _player_width / 2.0f, _arrow_y);
	drawTexture(_left_arrow, _arrow_left_x, _arrow_y);
	drawTexture(_right_arrow, _arrow_right_x, _arrow_y);
}

void GameEngine::drawEndGameSprites()
{
	drawTexture(_background, 0, 0);
	drawTexture(_play_again_button, _button_x, _play_button_y);
	drawTexture(_menu_button, _button_x, _menu_button_y);
	drawTexture(_score_bar, 0, 0);
	drawNumber(_managers.getPlatformManager().getPlatformsPassed(), 0, 0);
	drawNumber(_managers.getGameManager().getDistance(), _width / 3, 0);
}

void GameEngine::drawNumber(int number, int x, int y)
{
	std::string str = std::to_string(number);
	for (char c : str)
	{
		int digit = c - 48;
		drawTexture(_digit_sprites[digit], x, y);
		x += _digit_dimensions;
	}
}

void GameEngine::destroyTextures()
{
	SDL_DestroyTexture(_platform.tex);
	SDL_DestroyTexture(_background.tex);
	SDL_DestroyTexture(_score_bar.tex);
	SDL_DestroyTexture(_bullet.tex);
	for (int i = 0; i < DIGIT_COUNT; ++i)
		SDL_DestroyTexture(_digit_sprites[i].tex);
	for (int i = 0; i < ENEMY_COUNT; ++i)
		SDL_DestroyTexture(_enemy_sprites[i].tex);
	for (int i = 0; i < ABILITY_COUNT; ++i)
		SDL_DestroyTexture(_ability_sprites[i].tex);
	for (int i = 0; i < PLAYERLEFT_COUNT; ++i)
		SDL_DestroyTexture(_playerleft_sprites[i].tex);
	for (int i = 0; i < PLAYERRIGHT_COUNT; ++i)
		SDL_DestroyTexture(_playerright_sprites[i].tex);
	SDL_DestroyTexture(_play_button.tex);
	SDL_DestroyTexture(_play_again_button.tex);
	SDL_DestroyTexture(_menu_button.tex);
	SDL_DestroyTexture(_left_arrow.tex);
	SDL_DestroyTexture(_right_arrow.tex);
}

void GameEngine::createStart()
{
	_managers.getPlatformManager().createStart(_started, _managers.getGameManager().getX(), _platform_height);
}

void GameEngine::setFullscreen()
{
	if (_fullscreen)
	{
		SDL_GetWindowSize(this->getWindow(), &_width, &_height);
		initValues();
		_managers.getGameManager().setFullscreen(_width, _height);
		_managers.getAbilityManager().setFullscreen(_width, _height);
		_managers.getBulletManager().setFullscreen(_width, _height);
		_managers.getCollisionManager().setFullscreen(_width, _height);
		_managers.getEnemyManager().setFullscreen(_width, _height);
		_managers.getPlatformManager().setFullscreen(_width, _height);
		_fullscreen = false;
	}
}


void GameEngine::endGame()
{
	_lives -= 1;
	if (_lives == 0)
	{
		_lives = 5;
		_game_state = ENDGAME;
		_started = false;
		_managers.getPlatformManager().clearPlatforms();
	}
	_managers.getBulletManager().clearBullets();
	_managers.getAbilityManager().clearAbilities();
	_managers.getGameManager().setX(_managers.getPlatformManager().getPlatforms().front().x);
    _managers.getGameManager().setY(_managers.getPlatformManager().getPlatforms().front().y - (_player_height + _platform_height));
	_managers.getGameManager().gameReset();
	for (auto enemy = _managers.getEnemyManager().getEnemies().begin(); enemy != _managers.getEnemyManager().getEnemies().end();)
	{
		if (enemy->y > 0)
			enemy = _managers.getEnemyManager().eraseEnemy(enemy);
		else
			enemy++;
	}
}

void GameEngine::generateTimeDelta()
{
	unsigned int current_tick = SDL_GetTicks();;
	_delta_time = (current_tick - _last_tick) / 1000.0f;
	_last_tick = current_tick;
}

const char* GameEngine::GetTitle() { return "Doodle Jump"; }

inline SDL_Texture* GameEngine::loadTexture(const char *path)
{
	SDL_Texture *texture = IMG_LoadTexture(_renderer, path);
	if (texture == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load texture: %s", SDL_GetError());
		throw std::runtime_error("Runtime error LoadTexture thrown from GameEngine loadTexture");
	}
	return texture;
}

inline void GameEngine::drawTexture(const Texture& tex, float x, float y)
{
    SDL_FRect dst{ x, y, tex.w, tex.h };
    SDL_RenderTexture(_renderer, tex.tex, nullptr, &dst);
}