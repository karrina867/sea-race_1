#include "game.h"
#include "const.h"
#include <iostream>
Game::Game() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close),
	game_over_screen(IMAGES_FOLDER + GAME_OVER_FILE_NAME, 3.f, 3.f),
	menu_screen(IMAGES_FOLDER + MENU_FILE, 1.f, 1.f),
	lives_text(TEXT_FILE_NAME, 18, 520, 10, sf::Color::Black),
	intro_screen(IMAGES_FOLDER + INTRO_FILE_NAME, 0.70f, 0.80f),
	tim_text(TEXT_FILE_NAME, 30, 100, 600, sf::Color::Black),
	river1(0.f, 0.f),
	river2(0.f, -WINDOW_HEIGHT),
	player()
{
	window.setVerticalSyncEnabled(true);
	init();
}
void Game::init() {
	river1.init(0.f, 0.f);
	river2.init(0.f, -WINDOW_HEIGHT);
	player.init();
	lives = 3;
	bariers.clear();
	for (size_t i = 0; i < BARIER_QTY; i++) {
		Barier* barier = new Barier();
		bariers.push_back(barier);
	}
	island.clear();
	for (size_t i = 0; i < ISLANDS_TYPE_QTY; i++) {
		Islands* islands = new Islands();
		island.push_back(islands);
	}
	bonuses.clear();
	for (size_t i = 0; i < ISLANDS_TYPE_QTY; i++) {
		Bonus* bonus = new Bonus();
		bonuses.push_back(bonus);
	}
}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		check_collisions();
		draw();
	}
}
void Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
		if (game_state == GAME_OVER && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y) {
			game_state = INTRO;
			init();
		}
		else if (game_state == GAME_OVER && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
			game_state = GAME_OVER;
			exit(0);
		}
		if (event.type == sf::Event::KeyPressed) {
			if (game_state == INTRO && event.key.code == sf::Keyboard::Space) {
				game_state = PLAY;
			}
				if (game_state ==MENU && event.key.code == sf::Keyboard::Space) {
					game_state =INTRO;
				}
		}
	}
}
void Game::update() {
	switch (game_state) {
	case MENU:
		break;
	case INTRO:
		break;
	case PLAY:
		river1.update();
		river2.update();
		player.update();
		lives_text.update("Lives: " + std::to_string(lives));
		if (lives == 0) game_state = GAME_OVER;
		for (size_t i = 0; i < BARIER_QTY; i++) {
			bariers[i]->update();
		}
		for (size_t i = 0; i < BONUS_TYPES_QTY; i++) {
			bonuses[i]->update();
		}
		for (size_t i = 0; i < ISLANDS_TYPE_QTY; i++) {
			island[i]->update();
		}
		break;
	case GAME_OVER:
		tim_text.update(QUESTEN);
		break;
	}
}
void Game::draw() {
	switch (game_state) {
	case MENU:
		window.draw(menu_screen.getSprite());
		break;
	case INTRO:
		window.clear(sf::Color::Black);
		window.draw(game_over_screen.getSprite());
		break;
	case PLAY:
		river2.draw(window);
		river1.draw(window);
		player.draw(window);
		for (size_t i = 0; i < BARIER_QTY; i++) {
			bariers[i]->draw(window);
		};
		for (size_t i = 0; i < BONUS_TYPES_QTY; i++) {
				bonuses[i]->draw(window);
			
		};
		for (size_t i = 0; i < ISLANDS_TYPE_QTY; i++) {
			island[i]->draw(window);
		};
		window.draw(lives_text.getText());
		break;
	case GAME_OVER:
		window.clear(sf::Color(255, 222, 173));
		window.draw(intro_screen.getSprite());
		window.draw(tim_text.getText());
		break;
	}
	window.display();
}
void Game::check_collisions() {
	for (auto iter = bariers.begin(); iter != bariers.end(); iter++) {
		if (player.getHitBox().intersects((*iter)->getHitBox())) {
			lives = lives - 1;
			(*iter)->spawn();
			if (lives == 0) {
				game_state = GAME_OVER;
			}
		}
	}
	sf::Event event;
	window.pollEvent(event);
	for (auto ite_r = island.begin(); ite_r != island.end(); ite_r++) {
		if (player.getHitBox().intersects((*ite_r)->getHitBox())) {
			(*ite_r)->spawn();
			game_state = GAME_OVER;
		}
	}
	for (auto it_r = bonuses.begin(); it_r != bonuses.end(); it_r++) {
		if (player.getHitBox().intersects((*it_r)->getHitBox())) {
			(*it_r)->spawn();
			lives = lives +1;
		}
	}	
}