#pragma once

#include "ManagerContainer.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>

struct Texture {
    SDL_Texture* tex;
    float w, h;
};

enum class Key {
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT
};

enum class MouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

class GameEngine {
private:
	int				_width, _height;
	float			_digit_dimensions;
	float			_platform_height;
	float			_platform_width;
	float			_player_height;
	float			_player_width;
	float			_digit_size;
	float			_score_bar_height;
	float			_mouse_x, _mouse_y;
	bool			_started;
	int				_game_state;
	float			_button_x;
	float			_play_button_y, _menu_button_y;
	float			_button_width, _button_height;
	float			_arrow_size;
	float			_arrow_left_x, _arrow_right_x, _arrow_y;
	int				_lives;
	int				_costume_id;
	Texture			_play_button;
	Texture			_left_arrow;
	Texture			_right_arrow;
	Texture			_play_again_button;
	Texture			_menu_button;
	Texture			_platform;
	Texture			_background;
	Texture			_score_bar;
	Texture			_bullet;
	Texture		 	_playerleft_sprites[PLAYERLEFT_COUNT];
	Texture		 	_playerright_sprites[PLAYERRIGHT_COUNT];
	Texture		 	_digit_sprites[DIGIT_COUNT];
	Texture		 	_enemy_sprites[ENEMY_COUNT];
	Texture		 	_ability_sprites[ABILITY_COUNT];
	bool			_fullscreen;

	unsigned int	_last_tick;
	float			_delta_time;

	ManagerContainer	_managers;
	SDL_Window*			_window;
	SDL_Renderer*		_renderer;

public:

	GameEngine(int height, int width, bool fullscreen);
	~GameEngine();
	GameEngine(const GameEngine &other);
	GameEngine &operator=(const GameEngine &other);

	void		PreInit(int& width, int& height, bool& fullscreen);
	bool		init();
	void		Close();
	bool		Tick();
	void		initValues();
	void		GameView();
	void		EndGameView();
	void		MenuView();
	void		onMouseMove(int x, int y, int xrelative, int yrelative);
	void		onMouseButtonClick(MouseButton button, bool isReleased);
	void		onKeyPressed(Key k);
	void		onKeyReleased(Key k);
	bool		getMouseButtonClick(const Texture& tex, int x, int y) const;
	void 		generateTimeDelta();
	void		createTextures();
	void		drawGameSprites();
	void		drawMenuSprites();
	void		drawEndGameSprites();
	void		drawNumber(int number, int x, int y);
	void		destroyTextures();
	void		createStart();
	void		setFullscreen();
	void		endGame();
	const char*	GetTitle();

	SDL_Renderer*			getRenderer() { return _renderer; }
	SDL_Window*				getWindow() { return _window; }
	void					setRenderer(SDL_Renderer* renderer) { _renderer = renderer; }
	inline SDL_Texture*		loadTexture(const char* path);
	inline void				drawTexture(const Texture& tex, float x, float y);
};
