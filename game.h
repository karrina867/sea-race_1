#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include"const.h"
#include"river.h"
#include"barier.h"
#include"splash.h"
#include"text.h"
#include"island.h"
#include"Bonus.h"
#include<list>
#include <vector>
class Game {
public:
	enum GameState { MENU, INTRO, PLAY, GAME_OVER };
	Game();
	void play();
	void check_events();
	void update();
	void draw();
	void check_collisions();
	void init();
	size_t lives = 3;
private:
	sf::RenderWindow window;
	GameState game_state = MENU;
	Player player;
	River river1, river2;
	std::vector<Barier*> bariers;
	std::vector<Islands*> island;
	std::vector<Bonus*> bonuses;
	std::list<Player*> players;
	SplashScreen  intro_screen, game_over_screen, menu_screen;
	TextObject lives_text;
	TextObject tim_text;
};